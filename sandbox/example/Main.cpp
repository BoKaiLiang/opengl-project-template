#include "Core.h"

static float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, // right 
	 0.0f,  0.5f, 0.0f  // top   
};

class ExampleApplication : public Application
{
public:
	ExampleApplication(AppConfig config)
		: Application(config)
	{
		shader = Shader::Create("../assets/shaders/base_vert.glsl", "../assets/shaders/base_frag.glsl");

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	~ExampleApplication()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		delete shader;
	}

	virtual void OnUpdate(float dt) override
	{
		// DEBUG_INFO("Delta time: %f", dt);

		if (IsKeyPressed(KeyCode::Escape))
			ShutDown();
	}

	virtual void OnRender() override
	{
		shader->SetUniformVec3("u_Color", color);
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnImGui() override
	{
		ImGui::Begin("Debug");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(color));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

private:
	unsigned int VBO = 0, VAO = 0;
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	Shader* shader = nullptr;
};


int main(void)
{
	AppConfig config;
	config.m_Width = 800;
	config.m_Height = 600;
	config.m_DebugConfig = LogConfig::NOTHING;
	config.m_Title = "Example";

	auto app = new ExampleApplication(config);
	app->Run();
}