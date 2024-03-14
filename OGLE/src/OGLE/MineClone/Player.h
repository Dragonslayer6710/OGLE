#pragma once

#include "OGLE/Display/Renderer/Camera.h"

namespace OGLE
{
	class Application;
	class World;
	class AABB;

	class Player
	{
		Scope<Camera> m_Camera;
		static const glm::vec3 s_CameraOffset;
		static const glm::vec3 s_CrouchOffset;

		bool m_IsSprinting = false;
		bool m_IsCrouching = false;

		bool m_IsAttacking = false;
		float m_AttackCooldown = 0.0f;

		bool m_PausePressed = false;

		static const float s_WalkSpeed;
		static const float s_SprintSpeed;
		static const float s_CrouchSpeed;
		static const float s_DampingFactor;

		static const float Player::s_Gravity;
		static const float Player::s_TerminalVelocity;
		
		static const float s_JumpHeight;
		static const float s_JumpForceFactor;
		static const float s_JumpForce;

		float m_MoveSpeed = s_WalkSpeed;

		AABB m_AABB;

		Ref<glm::vec3> m_CameraPosition;
		Ref<glm::vec3> m_Orientation;
		Ref<glm::vec3> m_Up;

		glm::vec3 m_AABBPosition;

		glm::vec3 m_Velocity = glm::vec3(0.0f);
		glm::vec3 m_Acceleration = glm::vec3(0.0f);

		bool m_IsGrounded = true;
		bool m_DoesCollide = false;
		bool m_IsFlying = false;

		Ref<Cuboid> m_PlayerCuboid;
		Ref<Mesh> m_PlayerMesh;
		Ref<Model> m_PlayerModel;

		Ref<Instance> m_PlayerCuboidInstance;

		static const float s_PlayerReach;

	public:
		std::array<float, 6> collisions;

		static Scope<Player> Create()
		{
			return CreateScope<Player>();
		}

		Player();
		~Player();

		void Rotate();

		glm::vec3 MoveForward();

		glm::vec3 MoveBackward();

		glm::vec3 StrafeLeft();

		glm::vec3 StrafeRight();

		glm::vec3 Jump();

		glm::vec3 Crouch();

		void SetSprinting();

		void SetWalking();

		void SetCrouching();

		bool IsSprinting();

		bool IsCrouching();

		void Move(float deltaTime);

		glm::mat4 GetViewMatrix() const;

		glm::vec3 GetPosition();

		void SetPosition(glm::vec3 newPosition);

		glm::vec3 GetVelocity() { return m_Velocity; }

		void UpdatePlayer(float deltaTime);

		bool IsGrounded();

		void ToggleCollide();
		bool DoesCollide();

		void ToggleFlying();
		bool IsFlying();

		Ref<Model> GetPlayerModel();

		Ref<glm::vec3> GetCamPos() { return m_CameraPosition; }
		Ref<glm::vec3> GetOrientation() { return m_Orientation; }
		float GetPlayerReach() { return s_PlayerReach; }

	private:
		void CalculateAABBPosition();

		void SetAABBPosition();

		void SetSpeed(float moveSpeed);

		void ProcessInputAction(ControlID controlID);

		bool ResetPlayerStateIfNeeded(ControlID controlID);

		bool Player::NoInputDetected();

		void Player::UpdateMousePosition();

		bool HandleInput();

		void HandleMovementInput(std::vector<Control*> movements);

		void ApplyGravity();

		void HandleCollision();

		Ref<Block> GetRaycastBlock(const Raycast& raycast);

		void Attack();

	};

}
