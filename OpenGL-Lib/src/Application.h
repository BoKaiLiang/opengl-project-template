#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Event.h"
#include "Camera.h"

class Application {
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Application(unsigned int width, unsigned int height, const std::string& title);
	virtual ~Application();

	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

	void Run();
	void ShutDown();

	inline GLFWwindow* GetRawWindow() { return m_Window; }

	virtual void OnEvent(Event& e) = 0;
	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender() = 0;
	virtual void OnImGui() = 0;

	static Application& Get() { return *s_Instance; }

protected:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;

		EventCallbackFn EventCallback;
	};

	WindowData m_Data;

	static Application* s_Instance;

	Camera m_Camera;

protected:
	void WindowClear();
	void ImGuiClear();

	void WindowUpdate();
	void ImGuiRender();
};

#endif // _APPLICATION_H_