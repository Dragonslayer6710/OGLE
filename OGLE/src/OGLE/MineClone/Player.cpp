#include "oglepch.h"

#include "OGLE/MineClone/World.h"
#include "OGLE/Core/Application.h"
#include "OGLE/MineClone/Player.h"

#include <set>
namespace OGLE
{
	const glm::vec3 Player::s_CameraOffset = glm::vec3(0.0f, -1.0f, -2.0f);
	const glm::vec3 Player::s_CrouchOffset = glm::vec3(0.0f, -0.5f, 0.0f);

	const float Player::s_DampingFactor = 0.99f;

	const float Player::s_WalkSpeed = 2.0f;  // Let's say the walk speed is 1 unit per second
	const float Player::s_SprintSpeed = 1.5f * s_WalkSpeed;  // Sprint speed is 1.5 times the walk speed
	const float Player::s_CrouchSpeed = 0.7f * s_WalkSpeed;  // Crouch speed is 70% of the walk speed

	const float Player::s_Gravity = -9.8f;  // Standard Earth gravity
	const float Player::s_TerminalVelocity = -sqrt(2.0f* fabs(s_Gravity));  // Terminal velocity is 2 times the gravitational acceleration

	const float Player::s_JumpHeight = 1.0f;
	const float Player::s_JumpForce = sqrt(2.0f * fabs(s_Gravity) * s_JumpHeight);


	constexpr glm::vec3 c_PlayerDims = glm::vec3(0.5f, 2.0f, 0.5f);

	Player::Player()
		: m_Camera(Camera::Create(World::DecentreCoords()+s_CameraOffset+glm::vec3(0.0f, c_buildHeight / 4 * 5, 0.0f))),
		m_AABB(AABB::FromPos(glm::vec3(), c_PlayerDims))
	{
		m_PlayerCuboid = Cuboid::Create(1, c_PlayerDims);

		m_CameraPosition = m_Camera->GetPosition();
		m_Orientation = m_Camera->GetOrientation();
		m_Up = m_Camera->GetUp();

		m_PlayerCuboidInstance = (*m_PlayerCuboid->GetCuboidRefs(0, 1))[0];
		m_PlayerMesh = Mesh::Create(m_PlayerCuboid);
		m_PlayerModel = Model::Create(m_PlayerMesh);

		SetPosition();

	}

	Player::~Player()
	{
	}

	void Player::Rotate()
	{
		m_Camera->Rotate();
	}

	glm::vec3 Player::MoveForward()
	{
		if (!m_IsFlying) {
			// For regular movement (not flying), move in the direction of the camera's forward vector (x and z components)
			return glm::normalize(glm::vec3(m_Orientation->x, 0.0f, m_Orientation->z));
		}
		else {
			// For flying movement, move in the direction of the camera's orientation (considering all components)
			return *m_Orientation;
		}
	}

	glm::vec3 Player::MoveBackward()
	{
		if (!m_IsFlying) {
			// For regular movement (not flying), move in the opposite direction of the camera's forward vector (x and z components)
			return glm::normalize(glm::vec3(-m_Orientation->x, 0.0f, -m_Orientation->z));
		}
		else {
			// For flying movement, move in the opposite direction of the camera's orientation (considering all components)
			return - *m_Orientation;
		}
	}

	glm::vec3 Player::StrafeLeft()
	{
		// Calculate the left direction perpendicular to the camera's forward vector (xz plane)
		glm::vec3 forward = glm::normalize(glm::vec3(m_Orientation->x, 0.0f, m_Orientation->z));

		return -glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	glm::vec3 Player::StrafeRight()
	{
		// Calculate the forward direction perpendicular to the camera's forward vector (xz plane)
		glm::vec3 forward = glm::normalize(glm::vec3(m_Orientation->x, 0.0f, m_Orientation->z));

		// Calculate the right direction perpendicular to the forward direction (xz plane)
		return glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	}



	glm::vec3 Player::Jump()
	{
		if (!m_IsFlying) {
			// Only allow jumping if the player is grounded
			if (m_IsGrounded) {
				// Apply jump force to vertical velocity
				m_Velocity.y = s_JumpForce;

				// Update grounded state
				m_IsGrounded = false;

			}
			return glm::vec3(0.0f);
		}
		else {
			// When flying, move the player upwards along the y-axis
			return glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}


	glm::vec3 Player::Crouch()
	{
		if (!m_IsFlying) {			
			// If not flying, crouching behavior remains unchanged
			// You can add crouching behavior for non-flying state here if needed
			return glm::vec3(0.0f);
		}
		else {
			// When flying, move the player downwards along the y-axis
			return glm::vec3(0.0f, -1.0f, 0.0f);
		}
	}

	void Player::SetSpeed(float moveSpeed)
	{
		m_MoveSpeed = moveSpeed;
	}

	void Player::SetSprinting()
	{
		SetSpeed(s_SprintSpeed);
		m_IsSprinting = true;
	}

	void Player::SetWalking()
	{
		SetSpeed(s_WalkSpeed);
		m_IsSprinting = false;
		m_IsCrouching = false;
	}

	void Player::SetCrouching()
	{
		SetSpeed(s_CrouchSpeed);
		m_IsSprinting = false;
		m_IsCrouching = true;
	}

	void Player::ApplyGravity()
	{
		m_Acceleration.y += s_Gravity;
	}
	
	void Player::ProcessInputAction(ControlID controlID)
	{
		switch (controlID) {
		case CTRL_CFG_SPRINT:
			if (!m_IsSprinting)
				SetSprinting();
			break;
		case CTRL_CFG_CAMERA_CONTROL_TOGGLE:
			Application::Get().GetWindow().HideCursor();
			Rotate();
			break;
		default:
			break;
		}
	}

	void Player::ResetPlayerStateIfNeeded(ControlID controlID)
	{
		switch (controlID) {
		case CTRL_CFG_SPRINT:
			if (m_IsSprinting)
				SetWalking();
			break;
		case CTRL_CFG_CAMERA_CONTROL_TOGGLE:
			Application::Get().GetWindow().RevealCursor();
			break;
		default:
			break;
		}
	}

	bool Player::NoInputDetected()
	{
		// Check if any input is detected
		for (Control* boundCtrl : GetBoundControls()) {
			if (boundCtrl->GetInputState())
				return false;
		}
		return true;
	}

	void Player::UpdateMousePosition()
	{
		s_MousePosX = s_NextMousePosX;
		s_MousePosY = s_NextMousePosY;
	}

	void Player::HandleInput()
	{
		// Calculate mouse delta
		s_MouseDeltaX = s_NextMousePosX - s_MousePosX;
		s_MouseDeltaY = s_NextMousePosY - s_MousePosY;

		std::vector<Control*> movements;
		// Process input for each bound control
		for (Control* boundCtrl : GetBoundControls()) {
			if (boundCtrl->GetType() == CTRL_TYPE_MOVEMENT)
			{
				movements.emplace_back(boundCtrl);
			}
			else {
				if (boundCtrl->GetInputState()) {
					ProcessInputAction(boundCtrl->GetID());
				}
				else {
					ResetPlayerStateIfNeeded(boundCtrl->GetID());
				}
			}
		}
		if (!movements.empty())
			HandleMovementInput(movements);
		// Update mouse position for next frame
		UpdateMousePosition();
	}

	void Player::HandleMovementInput(std::vector<Control*> movements)
	{
		glm::vec3 moveVector(0.0f);
		for (const Control* ctrl: movements)
			if (ctrl->GetInputState())
				switch (ctrl->GetID()) {
				case CTRL_MOVE_FORWARD:
					moveVector += MoveForward();
					break;
				case CTRL_MOVE_LEFT:
					moveVector += StrafeLeft();
					break;
				case CTRL_MOVE_BACKWARD:
					moveVector += MoveBackward();
					break;
				case CTRL_MOVE_RIGHT:
					moveVector += StrafeRight();
					break;
				case CTRL_JUMP:
					moveVector += Jump();
					break;
				case CTRL_CROUCH:
					if (!m_IsCrouching)
						SetCrouching();
					moveVector += Crouch();
					break;
				}
			else
				switch (ctrl->GetID()) {
				case CTRL_CROUCH:
					if (m_IsCrouching)
						SetWalking();
					break;
				}
		if (moveVector.x == 0)
			m_Velocity.x = 0;
		if (m_IsFlying)
			if (moveVector.y == 0)
				m_Velocity.y = 0;
		if (moveVector.z == 0)
			m_Velocity.z = 0;
		m_Acceleration += moveVector * m_MoveSpeed;
	}


	void Player::Move(float deltaTime)
	{
		// Integrate acceleration to update velocity
		m_Velocity += m_Acceleration * deltaTime;

		// Cap horizontal speed
		float horizontalSpeed = glm::length(glm::vec2(m_Velocity.x, m_Velocity.z));
		if (horizontalSpeed > m_MoveSpeed) {
			float scale = m_MoveSpeed / horizontalSpeed;
			m_Velocity.x *= scale;
			m_Velocity.z *= scale;
		}

		if (m_IsFlying)
			if (m_Velocity.y > m_MoveSpeed)
				m_Velocity.y *= m_MoveSpeed / horizontalSpeed;

		// Update the player's position
		*m_CameraPosition += m_Velocity * deltaTime;

		// Update the player's AABB position
		SetPosition();

		// Handle collision with the environment
		HandleCollision();


		// Damp the velocity gradually to simulate deceleration
		/*m_Velocity *= s_DampingFactor;

		OGLE_CORE_INFO("\t- Player Velocity After Damping: {0}", m_Velocity);*/

		m_Acceleration = glm::vec3(0.0f);
	}


	void Player::HandleCollision() {
		// Obtain the list of blocks colliding with the player's AABB
		std::vector<Ref<Block>> collidingBlocks = World::Get()->GetCollidingBlocks(m_AABB);

		// Handle collision correction
		bool grounded = false; // Assume not grounded initially

		glm::vec3 correctionVector(0.0f);

		for (const auto& block : collidingBlocks) {
			// Ignore air blocks
			if (block->GetBlockID() == GLushort(-1))
				continue;

			glm::vec3 collisionDirection = roundToNearestHalf(m_AABB.calculateCollisionDirection(*block));

			float penetrationDepth = m_AABB.calculatePenetrationDepth(*block, collisionDirection);
			glm::vec3 correction = collisionDirection * penetrationDepth;

			correctionVector += correction;

			// Check if the player is grounded
			if (collisionDirection.y > 0.0f)
				grounded = true;
		}

		// If grounded or moving upward, cancel the y correction to prevent floating above ground
		if (grounded || m_Velocity.y > 0.0f)
			correctionVector.y = 0.0f;

		// Apply correction vector to player's position
		*m_CameraPosition += correctionVector;

		// Update the player's AABB position after collision handling
		SetPosition();

		// Update the player's grounded state
		m_IsGrounded = grounded;

		// Check if the player's grounded state has changed
		if (m_IsGrounded && m_Velocity.y < 0.0f) {
			// Reset the vertical velocity to zero
			m_Velocity.y = 0.0f;
		}
	}


	Ref<Model> Player::GetPlayerModel()
	{
		return m_PlayerModel;
	}

	bool Player::IsSprinting()
	{
		return m_IsSprinting;
	}

	bool Player::IsCrouching()
	{
		return m_IsCrouching;
	}

	glm::mat4 Player::GetViewMatrix() const
	{
		if (m_IsCrouching)
			return glm::lookAt(*m_CameraPosition + s_CrouchOffset, *m_CameraPosition + s_CrouchOffset + *m_Orientation, *m_Up);
		else
			return glm::lookAt(*m_CameraPosition, *m_CameraPosition + *m_Orientation, *m_Up);
	}

	glm::vec3 Player::GetPosition()
	{
		return *m_CameraPosition + s_CameraOffset;
	}

	void Player::SetPosition()
	{
		m_AABB = AABB::FromPos(GetPosition(), c_PlayerDims);
		m_PlayerCuboidInstance->ModelMatrix = NewModelMatrix(GetPosition());
		m_PlayerModel->UpdateVAO(true);
	}

	int frameCount = 0;
	void Player::UpdatePlayer(float deltaTime)
	{
		OGLE_CORE_INFO("Frame: {0}", ++frameCount);
		OGLE_CORE_INFO("\t- DeltaTime: {0}", deltaTime);

		// If the player is flying, move them based on velocity without considering gravity
		if (!m_IsFlying && !m_IsGrounded) {
			ApplyGravity();
		}

		// Handle player input
		HandleInput();

		// Move the player based on input and current state
		Move(deltaTime);
	}
	
	
	bool Player::IsGrounded()
	{
		return m_IsGrounded;
	}

	void Player::ToggleCollide()
	{
		m_DoesCollide = !m_DoesCollide;
	}

	bool Player::DoesCollide()
	{
		return m_DoesCollide;
	}

	void Player::ToggleFlying()
	{
		m_IsFlying = !m_IsFlying;
		if (m_IsFlying)
			m_IsGrounded = false;
	}

	bool Player::IsFlying()
	{
		return m_IsFlying;
	}
}