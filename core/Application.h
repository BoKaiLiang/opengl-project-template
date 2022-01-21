#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputCodes.h"
#include "Event.h"

class Application {
public:

	virtual ~Application();

	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

	virtual void Run();

	void ShutDown();

	inline GLFWwindow* GetRawWindow() { return m_Window; }

	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender() = 0;
	virtual void OnImGui() = 0;

	inline static Application& Get() { return *s_Instance; }

	// Input functions

	bool IsKeyPressed(KeyCode key);
	bool IsKeyReleased(KeyCode key);
	bool IsKeyDown(KeyCode key);
	bool IsKeyUp(KeyCode key);

	bool IsMouseButtonUp(Mouse mouse);
	bool IsMouseButtonDown(Mouse mouse);
	bool IsMouseButtonClick(Mouse mouse);

protected:
	GLFWwindow* m_Window;

	static Application* s_Instance;

	struct InputData
	{
		int m_CurrKeyBtnState[MAX_KEY_COUNT] = { 0 };
		int m_PrevKeyBtnState[MAX_KEY_COUNT] = { 0 };

		int m_CurrMouseBtnState[MAX_MOUSE_BUTTON_COUNT] = { 0 };
		int m_PrevMouseBtnState[MAX_MOUSE_BUTTON_COUNT] = { 0 };

		float m_MouseScrollOffset = 0.0f;

		glm::vec2 m_CursorPos;
	};

	InputData m_Input;

protected:
	Application(unsigned int width, unsigned int height, const std::string& title);

	void WindowClear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
	void ImGuiClear();

	void ImGuiRender();

	void UpdateInputState();
};

#endif // _APPLICATION_H_