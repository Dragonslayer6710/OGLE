#include "oglepch.h"
#include "HelloLayer.h"

#include "OGLE/Renderer/Shader.h"

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

	

	VertexBuffer* vbo;
	ElementBuffer* ebo;
	VertexArray* vao;
	static bool makeBuffers = true;
	void HelloLayer::OnUpdate(Timestep ts)
	{
		if (makeBuffers) {

			GLfloat vertices[]{
				-0.5f,  0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
				 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
				 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			};

			GLushort indices[]{
				0, 1, 2,
				0, 3, 2
			};

			vbo = new VertexBuffer(vertices, sizeof(vertices));
			vbo->AddVertexAttribute(VertAttribFloat2);
			vbo->AddVertexAttribute(VertAttribFloat4);

			ebo = new ElementBuffer(indices, sizeof(indices));


			vao = new VertexArray();
			vao->SetVertexBuffer(*vbo);
			vao->SetElementBuffer(*ebo);

			makeBuffers = false;

			ShaderProgram* shader = new ShaderProgram();
			shader->Activate();
			//ebo->Bind();
			//vao->Bind();
		}
		vao->Bind();
		//vbo->Bind();
		//ebo->Bind();
		//vao->Bind();

		
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}