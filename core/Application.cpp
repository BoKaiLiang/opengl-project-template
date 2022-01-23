#include "Application.h"

#include "WindowEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

#include "DebugLog.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

Application* Application::s_Instance = nullptr;

Application::Application(AppConfig config)
	: m_FrameTime(1.0 / (double)config.m_FPS)
{
	// Debug log config
	DebugLog::Init(config.m_DebugConfig);

	// Setup window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(config.m_Width, config.m_Height, config.m_Title.c_str(), NULL, NULL);
	if (m_Window == nullptr)
	{
		DEBUG_ERROR("Failed to create GLFW window");
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Input);

	// GLFW Callbacks
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputData& input= *(InputData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
			input.m_CurrKeyBtnState[key] = 1;
			break;
		case GLFW_RELEASE:
			input.m_CurrKeyBtnState[key] = 0;
			break;
		}
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		InputData& input = *(InputData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
			input.m_CurrMouseBtnState[button] = 1;
			break;
		case GLFW_RELEASE:
			input.m_CurrMouseBtnState[button] = 0;
			break;
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		InputData& input = *(InputData*)glfwGetWindowUserPointer(window);

		input.m_MouseScrollOffset = (float)yOffset;
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		InputData& input = *(InputData*)glfwGetWindowUserPointer(window);

		input.m_CursorPos.x = (float)xPos;
		input.m_CursorPos.y = (float)yPos;
	});


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG_ERROR("Failed to initialize GLAD");
	}
	glEnable(GL_DEPTH_TEST);

	// Setup ImGui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable 

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	s_Instance = this;
}

Application::~Application()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Application::Run()
{
	double lastTime = 0.0f;
	double currentTime = 0.0f;
	double elapsedTime = 0.0f;

	while (!glfwWindowShouldClose(m_Window)) {

		OnUpdate(elapsedTime);
		
		// Update time
		currentTime = glfwGetTime();
		double updateTime = currentTime - lastTime;
		lastTime = currentTime;

		WindowClear();
		ImGuiClear();

		OnRender();
		OnImGui();

		ImGuiRender();

		glfwSwapBuffers(m_Window);

		// Render time
		currentTime = glfwGetTime();
		double renderTime = currentTime - lastTime;
		lastTime = currentTime;

		// Fix timestep
		elapsedTime = updateTime + renderTime;
		if (elapsedTime < m_FrameTime)
		{
			WaitTime(m_FrameTime - elapsedTime);
			currentTime = glfwGetTime();
			double extraTime = currentTime - lastTime;
			lastTime = currentTime;

			elapsedTime += extraTime;
		}

		// Input state
		UpdateInputState();
		glfwPollEvents();
	}
}

void Application::ShutDown()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void Application::WaitTime(double wait)
{
	double end_time = 0.0f;
	double start_time = glfwGetTime();
	while ((end_time - start_time) < wait)
	{
		end_time = glfwGetTime();
	}
}

void Application::WindowClear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::ImGuiClear()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Application::ImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::UpdateInputState()
{
	m_Input.m_MouseScrollOffset = 0.0f;

	for (int i = 0; i < MAX_KEY_COUNT; i++)
	{
		m_Input.m_PrevKeyBtnState[i] = m_Input.m_CurrKeyBtnState[i];
		m_Input.m_CurrKeyBtnState[i] = 0;
	}

	for (int i = 0; i < MAX_MOUSE_BUTTON_COUNT; i++)
	{
		m_Input.m_PrevMouseBtnState[i] = m_Input.m_CurrMouseBtnState[i];
		m_Input.m_CurrMouseBtnState[i] = 0;
	}
}

bool Application::IsKeyPressed(KeyCode key)
{
	if (m_Input.m_PrevKeyBtnState[(int)key] == 0 && m_Input.m_CurrKeyBtnState[(int)key] == 1)
		return true;
	return false;
}

bool Application::IsKeyReleased(KeyCode key)
{
	if (m_Input.m_PrevKeyBtnState[(int)key] == 1 && m_Input.m_CurrKeyBtnState[(int)key] == 0)
		return true;
	return false;
}

bool Application::IsKeyDown(KeyCode key)
{
	if (m_Input.m_CurrKeyBtnState[(int)key] == 1)
		return true;
	return false;
}

bool Application::IsKeyUp(KeyCode key)
{
	if (m_Input.m_CurrKeyBtnState[(int)key] == 0)
		return true;
	return false;
}

bool Application::IsMouseButtonUp(Mouse mouse)
{
	if (m_Input.m_CurrMouseBtnState[(int)mouse] == 0)
		return true;
	return false;
}

bool Application::IsMouseButtonDown(Mouse mouse)
{
	if (m_Input.m_CurrMouseBtnState[(int)mouse] == 1)
		return true;
	return false;
}

bool Application::IsMouseButtonClick(Mouse mouse)
{
	if (m_Input.m_PrevMouseBtnState[(int)mouse] == 0 && m_Input.m_CurrMouseBtnState[(int)mouse] == 1)
		return true;
	return false;
}