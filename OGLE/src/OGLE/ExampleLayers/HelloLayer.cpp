#include "oglepch.h"
#include "OGLE/ExampleLayers/HelloLayer.h"
#include "OGLE/Geometry/Shape/Cube.h"
#include "OGLE/Geometry/Shape/Triangle.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ImGuizmo.h"

namespace OGLE {

	HelloLayer::HelloLayer(Renderer& renderer)
		: Layer("Hello Layer!"), m_Renderer(&renderer)
	{
		m_Camera = new Camera();
	}

	void HelloLayer::OnAttach()
	{
	}

	void HelloLayer::OnDetach()
	{
	}


	void HelloLayer::OnImGuiRender()
	{
		GLfloat FOVDegrees = m_Renderer->GetFOVDegrees();
		GLfloat NearPlane = m_Renderer->GetNearPlane();
		GLfloat FarPlane = m_Renderer->GetFarPlane();

		ImGui::SliderFloat("FOV", &FOVDegrees, 0.0f, 180.0f);
		m_Renderer->UpdateFOV(FOVDegrees);

		ImGui::SliderFloat("Near Plane", &NearPlane, 0.1f, 10.0f);
		ImGui::SliderFloat("Far Plane", &FarPlane, 0.1f, 10.0f);
		m_Renderer->UpdateClipPlanes(NearPlane, FarPlane);

		ImGui::SliderFloat3("Camera Position", &(m_Camera->m_Pos[0]), -10.0f, 10.0f);
		//ImGui::SliderFloat3("Far Plane", &FarPlane, 0.1f, 10.0f);
	}

	
	Cube* cube;
	Triangle* triangle;
	InstancedShape* instShape;

	ShaderProgram* shaderProgram;

	bool doInit = true;



	float xRot = 45.0f;
	float yRot = 45.0f;
	float zRot = 0.0f;
	VertexBuffer* vbo;
	ElementBuffer* ebo;
	VertexArray* vao;
	Camera* camera;
	void HelloLayer::OnUpdate(Timestep ts)
	{
		if (doInit) {
			glm::mat4 projMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());

			// Apply Translation
			glm::mat4 transMatrixA = glm::translate(glm::mat4(1.0), glm::vec3(-0.5f, 0.0f, -3.0f));
			glm::mat4 transMatrixB = glm::translate(glm::mat4(1.0), glm::vec3( 0.5f, 0.0f, -3.0f));

			// Apply Rotation...
			// ...in x
			glm::mat4 xRotMatrix = glm::rotate(glm::mat4(1.0), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
			// ...in y
			glm::mat4 xyRotMatrix = glm::rotate(xRotMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
			// ...in z
			glm::mat4 xyzRotMatrix = glm::rotate(xyRotMatrix, glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));

			std::vector<GLfloat> offsets = { -2.0f,0.f, 2.0f };
			std::vector<glm::mat4> instanceMatrices =
			{
				// Shape A
				transMatrixA * xyzRotMatrix,// glm::translate(projMatrix, glm::vec3(0.0f, 0.0f, -3.0f)),
				// Shape B
				transMatrixB * xyzRotMatrix,
			};

			shaderProgram = new ShaderProgram();

			//cube = new Cube();
			//triangle = new Triangle();
			vbo= new VertexBuffer(cubeVertices, instanceMatrices);
			ebo=  new ElementBuffer(cubeIndices);
			vao = new VertexArray(*vbo, *ebo);
			//instShape = new InstancedShape(*cube,offsets);
			//instShape = new InstancedShape(*triangle, instanceMatrices);

			m_Renderer->ChangeShaderProgram(*shaderProgram);
			m_Renderer->ChangeVAO(*vao);

			doInit = false;
		}

		xRot += 1.0f;
		if (xRot > 360)
			xRot = 0;
		yRot += 0.5f;
		if (yRot > 360)
			yRot = 0;
		zRot += 0.25f;
		if (zRot > 360)
			zRot = 0;
		
		// Init Projection Matrix
		glm::mat4 projMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());

		// Apply Translation
		glm::mat4 transMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
		
		// Apply Rotation...
		// ...in x
		glm::mat4 xRotMatrix = glm::rotate(glm::mat4(1.0), glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f));
		// ...in y
		glm::mat4 xyRotMatrix = glm::rotate(xRotMatrix, glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f));
		// ...in z
		glm::mat4 xyzRotMatrix = glm::rotate(xyRotMatrix, glm::radians(zRot), glm::vec3(0.0f, 0.0f, 1.0f));



		shaderProgram->SetUniformMatrix4fv("u_Projection", projMatrix);

		shaderProgram->SetUniformMatrix4fv("u_WorldToView", m_Camera->GetWorldToViewMatrix());

		shaderProgram->SetUniformMatrix4fv("u_Translation", transMatrix);
		shaderProgram->SetUniformMatrix4fv("u_Rotation", xyzRotMatrix);

		m_Renderer->Clear();
		//GLCall(glDrawElementsInstanced(GL_TRIANGLES, ebo->GetElementCount(), GL_UNSIGNED_SHORT, 0, 3));
		m_Renderer->Draw();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}