#include "oglepch.h"
#include "OGLE/Display/Layer/HelloLayer.h"
#include "OGLE/Maths/Geometry/3D/Cube.h"
#include "OGLE/Maths/Geometry/2D/Triangle.h"
#include "OGLE/Maths/Geometry/2D/Quad.h"
namespace OGLE {

	HelloLayer::HelloLayer(Renderer& renderer)
		: Layer("Hello Layer!"), m_Renderer(&renderer)
	{
		glfwGetCursorPos((GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow()),&s_MousePosX, &s_MousePosY);
		m_Camera = new Camera();
	}

	void HelloLayer::OnAttach()
	{
		InitControls();
	}

	void HelloLayer::OnEvent(Event& event)
	{
		switch(event.GetEventType())
		{
		case EventType::MouseButtonPressed:
		{
			MouseButtonPressedEvent mbpevent = (MouseButtonPressedEvent&)event;
			Input::SetState(mbpevent.GetMouseButton(), INPUT_STATE_PRESS);
			break;
		}
		case EventType::MouseButtonReleased:
		{
			MouseButtonReleasedEvent mbrevent = (MouseButtonReleasedEvent&)event;
			Input::SetState(mbrevent.GetMouseButton(), INPUT_STATE_RELEASE);
			break;
		}
		case EventType::MouseMoved:
		{
			MouseMovedEvent mmevent = (MouseMovedEvent&)event;
			s_NextMousePosX = mmevent.GetX();
			s_NextMousePosY = mmevent.GetY();
			break;
		}
		case EventType::MouseScrolled:
		{
			MouseScrolledEvent msevent = (MouseScrolledEvent&)event;
			s_ScrollOffsetX = msevent.GetXOffset();
			s_ScrollOffsetY = msevent.GetYOffset();
		}
		case EventType::KeyPressed:
		{
			KeyPressedEvent kpevent = ((KeyPressedEvent&)event);
			Input::SetState(kpevent.GetKeyCode(), INPUT_STATE_PRESS);
			break;
		}
		case EventType::KeyReleased:
			KeyReleasedEvent krevent = ((KeyReleasedEvent&)event);
			Input::SetState(krevent.GetKeyCode(), INPUT_STATE_RELEASE);
			break;
		}
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

		//ImGui::SliderFloat3("Camera Position", &(m_Camera->m_Pos[0]), -10.0f, 10.0f);
		//ImGui::SliderFloat3("Far Plane", &FarPlane, 0.1f, 10.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	ShaderProgram* shaderProgram;

	bool doInit = true;



	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	VertexBuffer* vbo;
	ElementBuffer* ebo;
	VertexArray* vao;
	Camera* camera;

	Triangle* triangle;
	Quad* quad;
	Cube* cube;

	UniformTextureAtlas* texture;
	glm::vec2* texAtlasSize;
	glm::vec2* textureOffset;
	void HelloLayer::OnUpdate(Timestep ts)
	{
		if (doInit) {
			glm::mat4 projMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());

			// Apply Translation
			shaderProgram = new ShaderProgram();

			//vao = Cubes();
			//instShape = new InstancedShape(*cube,offsets);
			//instShape = new InstancedShape(*triangle, instanceMatrices);
			//triangle = new Triangle();

			texture = new UniformTextureAtlas("terrain.png",glm::vec2(16,16));
			InstanceList instList = InstanceList
			({
				Instance{glm::translate(glm::mat4(1.0f), glm::vec3(-0.5,0,0)) * glm::rotate(glm::mat4(1.0f),glm::radians(90.0f),glm::vec3(0.0f, 1.0f, 0.0f)), texture->GetSubTexture(0).Position,texture->GetSubTexture(0).Size},
				Instance{glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-0.5)), texture->GetSubTexture(1).Position,texture->GetSubTexture(1).Size},
				Instance{glm::translate(glm::mat4(1.0f), glm::vec3(0,-0.5,0)) * glm::rotate(glm::mat4(1.0f),glm::radians(90.0f),glm::vec3(1.0f, 0.0f, 0.0f)), texture->GetSubTexture(2).Position,texture->GetSubTexture(2).Size}
				});
			quad = new Quad
			(
				&instList 
			);
			//quad = new Quad();
			//cube = new Cube();
			
			vao = &(quad->GetVAO());

			
			

			m_Renderer->ChangeShaderProgram(*shaderProgram);
			m_Renderer->ChangeVAO(*vao);

			shaderProgram->SetUniform1i("tex0", 0);
			
			doInit = false;
			
		}
		
		// Init Projection Matrix
		glm::mat4 viewToProjectionMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());
		glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * m_Camera->GetWorldToViewMatrix();

		shaderProgram->SetUniformMatrix4fv("u_WorldToProjection", worldToProjectionMatrix);
		
		s_MouseDeltaX = s_NextMousePosX - s_MousePosX;
		s_MouseDeltaY = s_NextMousePosY - s_MousePosY;
		
		for (Control* boundCtrl : GetBoundControls()) {
			if (boundCtrl->GetInputState())
				switch (boundCtrl->GetID())
				{
				case CTRL_MOVE_FORWARD:
					m_Camera->MoveForward();
					break;
				case CTRL_MOVE_LEFT:
					m_Camera->StrafeLeft();
					break;
				case CTRL_MOVE_BACKWARD:
					m_Camera->MoveBackward();
					break;
				case CTRL_MOVE_RIGHT:
					m_Camera->StrafeRight();
					break;
				case CTRL_MOVE_UP:
					m_Camera->MoveUp();
					break;
				case CTRL_MOVE_DOWN:
					m_Camera->MoveDown();
					break;
				case CTRL_CFG_CAMERA_CONTROL_TOGGLE:
					Application::Get().GetWindow().HideCursor();
					m_Camera->Rotate();
				}
			else
				switch (boundCtrl->GetID())
				{
				case CTRL_CFG_CAMERA_CONTROL_TOGGLE:
					Application::Get().GetWindow().RevealCursor();
					break;
				default:
					break;
				}
		}

		s_MousePosX = s_NextMousePosX;
		s_MousePosY = s_NextMousePosY;

		m_Renderer->Clear();
		//GLCall(glDrawElementsInstanced(GL_TRIANGLES, ebo->GetElementCount(), GL_UNSIGNED_SHORT, 0, 3));
		m_Renderer->Draw();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}