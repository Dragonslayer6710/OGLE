#include "oglepch.h"
#include "OGLE/ExampleLayers/HelloLayer.h"

#include "OGLE/Renderer/Renderer.h"

namespace OGLE {

	HelloLayer::HelloLayer()
		:Layer("Hello Layer!")
	{
		
	}

	void HelloLayer::OnAttach()
	{
	}

	void HelloLayer::OnDetach()
	{
	}

	

	std::vector<Vertex> vertices =
	{
		Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec4(0.0f, 1.0f, 0.5f, 1.0f)},
		Vertex{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f,  0.0f,  0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, -0.5f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}
	};

	std::vector<GLushort> indices =
	{
		0, 1, 2,
		0, 3, 2
	};

	VertexBuffer* vbo;
	ElementBuffer* ebo;
	VertexArray* vao;
	
	ShaderProgram* shaderProgram;


	Renderer* renderer;

	bool doInit = true;

	void HelloLayer::OnUpdate(Timestep ts)
	{
		if (doInit) {
			vbo = new VertexBuffer(vertices);
			ebo = new ElementBuffer(indices);
			vao = new VertexArray(*vbo, *ebo);

			shaderProgram = new ShaderProgram();
			renderer = new Renderer(*shaderProgram, *vao);

			//shaderProgram->Activate();
			doInit = false;
		}
		//vao->Bind();
		renderer->Clear();
		renderer->Draw();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}