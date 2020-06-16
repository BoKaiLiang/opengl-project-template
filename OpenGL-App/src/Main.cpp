#include "Entry.h"
#include "Input.h"
#include "Texture.h"
#include "Shader.h"

#include <imgui.h>
#include <string>

#include <tiny_obj_loader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class App : public Application
{
public:
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;

	};

	App(unsigned int width, unsigned int height, const std::string& title)
		: Application(width, height, title), 
		modelShader("assets/shaders/model.vs", "assets/shaders/model.fs"),
		modelVBO(0), modelVAO(0)
	{
		std::string warn_msg, err_msg;
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn_msg, &err_msg, 
			"assets/models/Monkey/Monkey.obj",
			"assets\\models\\Monkey");

		if (!warn_msg.empty()) {
			std::cout << warn_msg << std::endl;
		}

		if (!err_msg.empty()) {
			std::cerr << err_msg << std::endl;
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					Vertex vertex{ };

					vertex.Position = {
						attrib.vertices[3 * idx.vertex_index + 0],
						attrib.vertices[3 * idx.vertex_index + 1],
						attrib.vertices[3 * idx.vertex_index + 2]
					};

					vertex.Normal = {
						attrib.normals[3 * idx.normal_index + 0],
						attrib.normals[3 * idx.normal_index + 1],
						attrib.normals[3 * idx.normal_index + 2]
					};

					vertex.TexCoord = {
						attrib.texcoords[2 * idx.texcoord_index + 0],
						1 - attrib.texcoords[2 * idx.texcoord_index + 1]
					};

					vertices.push_back(vertex);
				}
				index_offset += fv;
			}
		}

		glGenVertexArrays(1, &modelVAO);
		glGenBuffers(1, &modelVBO);

		glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


		glBindVertexArray(modelVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offsetof(Vertex, Position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offsetof(Vertex, Normal)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offsetof(Vertex, TexCoord)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	~App()
	{

	}

	virtual void OnEvent(Event& e) override
	{
		
	}

	virtual void OnUpdate(float dt) override
	{
		if (Input::IsKeyPressed(KeyCode::W))
			m_Camera.ProcessKeyboard(CameraMovement::FORWARD, dt);
		if (Input::IsKeyPressed(KeyCode::S))
			m_Camera.ProcessKeyboard(CameraMovement::BACKWARD, dt);
		if (Input::IsKeyPressed(KeyCode::A))
			m_Camera.ProcessKeyboard(CameraMovement::LEFT, dt);
		if (Input::IsKeyPressed(KeyCode::D))
			m_Camera.ProcessKeyboard(CameraMovement::RIGHT, dt);

		glm::mat4 projection = glm::perspective(glm::radians(m_Camera.Zoom), (float)m_Data.Width / (float)m_Data.Height, 0.1f, 100.0f);
		glm::mat4 view = m_Camera.GetViewMatrix();

		glUseProgram(modelShader.GetID());
		modelShader.SetUniformMat4("projection", projection);
		modelShader.SetUniformMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		modelShader.SetUniformMat4("model", model);
	}

	virtual void OnRender() override
	{

		glBindVertexArray(modelVAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);
	}

	virtual void OnImGui() override
	{
		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

private:
	std::vector<Vertex> vertices;
	Shader modelShader;

	unsigned modelVBO, modelVAO;
};

Application* CreateApplication()
{
	return new App(1280, 720, "Engine");
}