#include "oglepch.h"
#include "OGLE/Display/Layer/HelloLayer.h"
#include "OGLE/Maths/Geometry/Shape/Cube.h"
#include "OGLE/Maths/Geometry/Shape/Triangle.h"

#include "OGLE/Input/Control.h"
#include "OGLE/Core/Application.h"
namespace OGLE {

	HelloLayer::HelloLayer(Renderer& renderer)
		: Layer("Hello Layer!"), m_Renderer(&renderer)
	{
		double initMouseX, initMouseY;
		glfwGetCursorPos((GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow()),&initMouseX, &initMouseY);
		m_Camera = new Camera(glm::vec2(initMouseX, initMouseY));
	}

	void HelloLayer::OnAttach()
	{
		ControlBinds = std::unordered_map<ControlID,ControlBind*>();
		s_ControlStates = new std::unordered_map<ControlID, ControlState*>();
		NewKeyBind(CTRL_MOVE_FORWARD, Key::W);
		NewKeyBind(CTRL_MOVE_LEFT, Key::A);
		NewKeyBind(CTRL_MOVE_BACKWARD, Key::S);
		NewKeyBind(CTRL_MOVE_RIGHT, Key::D);		

		NewMouseButtonBind(CTRL_ENABLE_ROTATE, Mouse::ButtonLeft);
	}

	void HelloLayer::OnEvent(Event& event)
	{
		switch(event.GetEventType())
		{
		case EventType::MouseButtonPressed:
		{
			MouseButtonPressedEvent mbpevent = (MouseButtonPressedEvent&)event;
			SetMouseBtnState(mbpevent.GetMouseButton(), INPUT_PRESS);
			break;
		}
		case EventType::MouseButtonReleased:
		{
			MouseButtonReleasedEvent mbrevent = (MouseButtonReleasedEvent&)event;
			SetMouseBtnState(mbrevent.GetMouseButton(), INPUT_RELEASE);
			break;
		}
		case EventType::MouseMoved:
		{
			MouseMovedEvent mmevent = (MouseMovedEvent&)event;
			break;
		}
		case EventType::MouseScrolled:
		{
			MouseScrolledEvent msevent = (MouseScrolledEvent&)event;
			SetScrollOffset(glm::vec2(msevent.GetXOffset(), msevent.GetYOffset()));
		}
		case EventType::KeyPressed:
		{
			KeyPressedEvent kpevent = ((KeyPressedEvent&)event);
			SetKeyState(kpevent.GetKeyCode(), INPUT_PRESS);
			break;
		}
		case EventType::KeyReleased:
			KeyReleasedEvent krevent = ((KeyReleasedEvent&)event);
			SetKeyState(krevent.GetKeyCode(), INPUT_RELEASE);
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
		if (m_Camera->GetControlState())
			glfwSetInputMode((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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


		for (auto& kv : ControlBinds) {
			ControlBind* ctrlBind = (ControlBind*)kv.second;
			if (ctrlBind->GetState())
				switch (ctrlBind->GetID())
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
				case CTRL_ENABLE_ROTATE:
					m_Camera->Rotate(Application::Get().GetWindow());
				}
		}


		m_Renderer->Clear();
		//GLCall(glDrawElementsInstanced(GL_TRIANGLES, ebo->GetElementCount(), GL_UNSIGNED_SHORT, 0, 3));
		m_Renderer->Draw();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}