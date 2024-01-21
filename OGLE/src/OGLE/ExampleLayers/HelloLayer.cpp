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


	std::vector<Vertex> cubeVertices =
	{
		Vertex{glm::vec3( 1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //0 Right
		Vertex{glm::vec3( 1.0f,-1.0f,-1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //1
		Vertex{glm::vec3( 1.0f, 1.0f,-1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //2
		Vertex{glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //3

		Vertex{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //4 Left
		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //5
		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //6
		Vertex{glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //7

		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //8 Top
		Vertex{glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //9
		Vertex{glm::vec3( 1.0f, 1.0f,-1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //10
		Vertex{glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //11

		Vertex{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //12 Bottom
		Vertex{glm::vec3( 1.0f,-1.0f,-1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //13
		Vertex{glm::vec3( 1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //14
		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //15

		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //16 Front
		Vertex{glm::vec3( 1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //17
		Vertex{glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //18
		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //19

		Vertex{glm::vec3( 1.0f,-1.0f, -1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //20 Back
		Vertex{glm::vec3(-1.0f,-1.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //21
		Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //22
		Vertex{glm::vec3( 1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //23
	};

	std::vector<GLushort> cubeIndices =
	{
		 0,  1,  2,
		 2,  3,  0,

		 4,  5,  6,
		 6,  7,  4,
		
		8,  9, 10,
		10, 11,  8,
		
		12, 13, 14,
		14, 15, 12,
		
		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,

	};
	

	std::vector<Vertex> triVertices =
	{
		Vertex{glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3( 1.0f, -1.0f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
		//Vertex{glm::vec3( 0.0f, -0.5f,  0.0f), glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f)}
	};

	std::vector<GLushort> triIndices =
	{
		0, 1, 2,
		//0, 3, 2
	};

	VertexBuffer* vbo;
	ElementBuffer* ebo;
	VertexArray* vao;
	
	ShaderProgram* shaderProgram;


	Renderer* renderer;

	bool doInit = true;
	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	void HelloLayer::OnUpdate(Timestep ts)
	{
		if (doInit) {
			vbo = new VertexBuffer(cubeVertices);
			ebo = new ElementBuffer(cubeIndices);
			vao = new VertexArray(*vbo, *ebo);

			shaderProgram = new ShaderProgram();
			renderer = new Renderer(*shaderProgram, *vao);

			//shaderProgram->Activate();
			doInit = false;
			glViewport(0, 0, 640, 640);
		}
		//vao->Bind();
		xRot += 1.0f;
		if (xRot > 360)
			xRot = 0;
		yRot += 0.5f;
		if (yRot > 360)
			yRot = 0;
		zRot += 0.25f;
		if (zRot > 360)
			zRot = 0;
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 xRotation = glm::rotate(glm::mat4(1.0f), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 yRotation = glm::rotate(glm::mat4(1.0f), glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 zRotation = glm::rotate(glm::mat4(1.0f), glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotation = xRotation * yRotation * zRotation;

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 10.0f);

		shaderProgram->SetUniformMatrix4fv("u_Transformation", projection * translation * rotation);

		renderer->Clear();
		renderer->Draw();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}