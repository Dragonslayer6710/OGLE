#include "oglepch.h"
#include "OGLE/Display/Layer/GameWorldLayer.h"
#include "OGLE/MineClone/World.h"

namespace OGLE {

	GameWorldLayer::GameWorldLayer(Renderer& renderer)
		: Layer("Game World Layer!"), m_Renderer(&renderer)
	{
		//testOctree();
		//delete[] this;
		glfwGetCursorPos((GLFWwindow*)(Application::Get().GetWindow().GetNativeWindow()), &s_MousePosX, &s_MousePosY);
	}

	void GameWorldLayer::OnAttach()
	{
		InitControls();
		m_Renderer->AddHUDElement(CreateScope<HUDCrosshair>());
	}

	void GameWorldLayer::OnEvent(Event& event)
	{
		switch (event.GetEventType())
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

	void GameWorldLayer::OnDetach()
	{
	}

	bool newWorld = true;


	Ref<World> world;
	Ref<Player> player;

	Scope<WorldRenderer> worldRenderer;

	void GameWorldLayer::OnImGuiRender()
	{
		GLfloat FOVDegrees = m_Renderer->GetFOVDegrees();
		GLfloat NearPlane = m_Renderer->GetNearPlane();
		GLfloat FarPlane = m_Renderer->GetFarPlane();

		ImGui::SliderFloat("FOV", &FOVDegrees, 0.0f, 180.0f);
		m_Renderer->UpdateFOV(FOVDegrees);

		ImGui::SliderFloat("Near Plane", &NearPlane, 0.1f, 10.0f);
		ImGui::SliderFloat("Far Plane", &FarPlane, 0.1f, 1000.0f);

		ImGui::Text((player->IsGrounded()) ? "Grounded: True" : "Grounded: False");

		ImGui::Text("WestCollide: %.3f", player->collisions[0]);
		ImGui::Text("EastCollide: %.3f", player->collisions[1]);
		ImGui::Text("BottomCollide: %.3f", player->collisions[2]);
		ImGui::Text("TopCollide: %.3f", player->collisions[3]);
		ImGui::Text("SouthCollide: %.3f", player->collisions[4]);
		ImGui::Text("NorthCollide: %.3f", player->collisions[5]);

		ImGui::InputFloat3("Position:", &player->GetPosition()[0]);

		ImGui::InputFloat3("Velocity:", &player->GetVelocity()[0]);

		if (!newWorld)
			if (ImGui::Button("New World"))
				newWorld = true;

		if (ImGui::Button((player->DoesCollide()) ? "Collision: Enabled" : "Collision: Disabled"))
			player->ToggleCollide();

		if (ImGui::Button((player->IsFlying()) ? "Flying: Enabled" : "Flying: Disabled"))
			player->ToggleFlying();

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


	Scope<ShaderProgram> m_HUDShaderProgram;

	void GameWorldLayer::OnUpdate(double deltaTime)
	{
		if (doInit) {
			glm::mat4 projMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());

			// Apply Translation
			shaderProgram = new ShaderProgram();

			std::string shaders[2] = { "HUD", "HUD" };
			m_HUDShaderProgram = CreateScope<ShaderProgram>(shaders);

			m_Renderer->ChangeShaderProgram(*shaderProgram);

			doInit = false;

		}
		if (newWorld) {
			world = World::Create();
			player = world->GetPlayer();
			m_Renderer->AddHUDElement(CreateScope<HUDViewRaycast>(player->GetCamPos(), player->GetOrientation(), player->GetPlayerReach()));

			worldRenderer = CreateScope<WorldRenderer>(world);

			Ref<Model> worldModel = worldRenderer->GetWorldModel();
			m_Renderer->RemoveModel(worldModel);
			m_Renderer->AddModel(worldModel);

			//Ref<Model> playerModel = player->GetPlayerModel();
			//m_Renderer->RemoveModel(playerModel);
			//m_Renderer->AddModel(playerModel);

			newWorld = false;
		}

		// Init Projection Matrix
		glm::mat4 viewMatrix = world->GetViewMatrix();
		glm::mat4 projMatrix = glm::perspective(m_Renderer->GetFOV(), m_Renderer->GetAspectRatio(), m_Renderer->GetNearPlane(), m_Renderer->GetFarPlane());

		player->UpdatePlayer(deltaTime);

		m_Renderer->Clear();
		//GLCall(glDrawElementsInstanced(GL_TRIANGLES, ebo->GetElementCount(), GL_UNSIGNED_SHORT, 0, 3));
		m_Renderer->ChangeShaderProgram(*shaderProgram);
		shaderProgram->SetUniformMatrix4fv("u_ProjViewMatrix", projMatrix * viewMatrix);
		m_Renderer->Draw();

		m_Renderer->ChangeShaderProgram(*m_HUDShaderProgram);
		m_HUDShaderProgram->SetUniformMatrix4fv("u_ProjViewMatrix", projMatrix * viewMatrix);
		m_Renderer->DrawHUD();
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
	}

}