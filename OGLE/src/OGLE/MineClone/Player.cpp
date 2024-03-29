#include "oglepch.h"

#include "OGLE/MineClone/World.h"
#include "OGLE/Core/Application.h"
#include "OGLE/MineClone/Player.h"

#include <set>
namespace OGLE
{
	const glm::vec3 Player::s_CameraOffset = glm::vec3(0.0f, -0.81f, 0.0f);
	const glm::vec3 Player::s_CrouchOffset = glm::vec3(0.0f, -0.5f, 0.0f);

	const float Player::s_DampingFactor = 0.99f;

	const float Player::s_WalkSpeed = 2.0f;  // Let's say the walk speed is 1 unit per second
	const float Player::s_SprintSpeed = 1.5f * s_WalkSpeed;  // Sprint speed is 1.5 times the walk speed
	const float Player::s_CrouchSpeed = 0.7f * s_WalkSpeed;  // Crouch speed is 70% of the walk speed

	const float Player::s_Gravity = -9.8f;  // Standard Earth gravity
	const float Player::s_TerminalVelocity = -sqrt(2.0f* fabs(s_Gravity));  // Terminal velocity is 2 times the gravitational acceleration

	const float Player::s_JumpHeight = 1.1f;
	const float Player::s_JumpForce = sqrt(2.0f * fabs(s_Gravity) * s_JumpHeight);

	const float Player::s_PlayerReach = 4.5f;

	constexpr glm::vec3 c_PlayerDims = glm::vec3(0.6f, 1.8f, 0.6f);

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

		SetAABBPosition();

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

	glm::vec3 Player::GetPosition()
	{
		return m_AABBPosition - glm::vec3(0.0f,0.4f,0.0f);
	}

	void Player::SetPosition(glm::vec3 position)
	{
		*m_CameraPosition = position + glm::vec3(0.0f, 0.4f, 0.0f) - s_CameraOffset;
		SetAABBPosition();
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
		case CTRL_ACTION_SPRINT:
			if (!m_IsSprinting)
				SetSprinting();
			break;
		case CTRL_ACTION_ATTACK:
			if (!m_IsAttacking)
				m_IsAttacking = true;
			break;
		case CTRL_CFG_PAUSE_TOGGLE:
			m_PausePressed = true;
			break;
		default:
			break;
		}
	}

	bool Player::ResetPlayerStateIfNeeded(ControlID controlID)
	{
		switch (controlID) {
		case CTRL_ACTION_SPRINT:
			if (m_IsSprinting)
				SetWalking();
			break;
		case CTRL_ACTION_ATTACK:
			if (m_IsAttacking)
				m_IsAttacking = false;
			break;
		case CTRL_CFG_PAUSE_TOGGLE:
			if (m_PausePressed) {
				m_PausePressed = false;
				World::Get()->TogglePause();
				return World::Get()->GetPaused();
			}
			break;
		default:
			break;
		}
		return false;
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

	bool Player::HandleInput()
	{
		// Calculate mouse delta
		s_MouseDeltaX = s_NextMousePosX - s_MousePosX;
		s_MouseDeltaY = s_NextMousePosY - s_MousePosY;

		std::vector<Control*> movements;
		bool paused = false;
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
					if (ResetPlayerStateIfNeeded(boundCtrl->GetID()))
					{
						paused = true;
					}
				}
			}
		}
		if (!paused)
			paused = World::Get()->GetPaused();
		if (paused)
		{
			Application::Get().GetWindow().RevealCursor();
			return paused;
		}
		else
			Application::Get().GetWindow().HideCursor();

		Rotate();

		if (!movements.empty())
			HandleMovementInput(movements);
		// Update mouse position for next frame
		UpdateMousePosition();

		return false;
	}

	void Player::HandleMovementInput(std::vector<Control*> movements)
	{
		glm::vec3 moveVector(0.0f);
		for (const Control* ctrl : movements) {
			glm::vec3 extraMovement(0.0f);
			if (ctrl->GetInputState())
				switch (ctrl->GetID()) {
				case CTRL_MOVE_FORWARD:
					extraMovement = MoveForward();
					break;
				case CTRL_MOVE_LEFT:
					extraMovement = StrafeLeft();
					break;
				case CTRL_MOVE_BACKWARD:
					extraMovement = MoveBackward();
					break;
				case CTRL_MOVE_RIGHT:
					extraMovement = StrafeRight();
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
			if (extraMovement != glm::vec3(0.0f)) {
				if (m_IsFlying)
					moveVector += extraMovement;
				else
					moveVector += extraMovement * m_MoveSpeed;
			}
			else
				switch (ctrl->GetID()) {
				case CTRL_CROUCH:
					if (m_IsCrouching)
						SetWalking();
					break;
				}
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

	Ref<Block> Player::GetRaycastBlock(const Raycast& raycast)
	{
		return World::Get()->GetRaycastBlock(raycast);
	}

	void Player::Attack()
	{
		m_AttackCooldown = 2.0f;
		Raycast raycast = m_Camera->GetRaycast(s_PlayerReach);

		Raycast raycastCopy = raycast;
		Ref<Block> hitBlock;
		std::pair<glm::vec3, glm::vec3> blockRaycastIntersections;
		std::vector<glm::vec3> rcVecs = raycast.GetVectors();

		do {
			hitBlock = GetRaycastBlock(raycastCopy);

			if (hitBlock != nullptr) {
				if (hitBlock->GetBlockID() != GLushort(-1)) {
					OGLE_CORE_INFO("Block at {0} Hit!", hitBlock->getCenter());
					break;
				}
				else if (hitBlock->GetBlockID() == GLushort(-1))
				{
					blockRaycastIntersections = hitBlock->getRaycastIntersections(raycastCopy);
					if (blockRaycastIntersections.second == glm::vec3())
						break;
					else {
						rcVecs = raycastCopy.GetVectors();
						glm::vec3 diff = rcVecs[2] - rcVecs[0];
						float length = glm::length(diff);
						raycastCopy = Raycast(blockRaycastIntersections.second + rcVecs[1], rcVecs[1], rcVecs[2]);
					}
				}
			}
			else
				OGLE_CORE_INFO("No Block Hit!");
		} while (hitBlock != nullptr);
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
		SetAABBPosition();

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
		collisions = { 0, 0, 0, 0, 0, 0 };
		for (const auto& block : collidingBlocks) {
			// Ignore air blocks
			if (block->GetBlockID() == GLushort(-1))
				continue;

			glm::vec3 correction = m_AABB.calculateCollisionCorrection(*block);
			
			glm::vec3 collisionDirection = m_AABB.calculateCorrectionDirection(*block, correction);
			
			correctionVector += correction * collisionDirection;

			if (collisionDirection.x)
				if (collisionDirection.x < 0.0f)
					collisions[1] = collisionDirection.x;
				else
					collisions[0] = collisionDirection.x;
			if (collisionDirection.y)
				if (collisionDirection.y < 0.0f)
					collisions[3] = collisionDirection.y;
				else
					collisions[2] = collisionDirection.y;
			if (collisionDirection.z)
				if (collisionDirection.z < 0.0f)
					collisions[5] = collisionDirection.z;
				else
					collisions[4] = collisionDirection.z;

			if (collisionDirection.y) {
				// Check if the player is grounded
				if (collisionDirection.y == 1.0f)
					grounded = true;
				else if (collisionDirection.y == -1.0f)
					if (m_Velocity.y <= 0.0f)
						correctionVector -= correction.y;
				m_Velocity.y = 0.0f;
			}
			else {
				//m_Velocity *= 0.1f * collisionDirection;
				if (collisionDirection.x)
					m_Velocity.x = 0.0f;
				else
					m_Velocity.z = 0.0f;
				correctionVector += collisionDirection * 0.001f;
			}
		}

		// Apply correction vector to player's position
		*m_CameraPosition += correctionVector;

		// Update the player's AABB position after collision handling
		SetAABBPosition();

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

	void Player::CalculateAABBPosition()
	{
		m_AABBPosition = *m_CameraPosition + s_CameraOffset;
	}


	void Player::SetAABBPosition()
	{
		CalculateAABBPosition();
		m_AABB = AABB::FromPos(m_AABBPosition, c_PlayerDims);
		m_PlayerCuboidInstance->ModelMatrix = NewModelMatrix(m_AABBPosition);
		m_PlayerModel->UpdateVAO(true);
	}

	int frameCount = 0;
	void Player::UpdatePlayer(float deltaTime)
	{
		//OGLE_CORE_INFO("Frame: {0}", ++frameCount);
		//OGLE_CORE_INFO("\t- DeltaTime: {0}", deltaTime);

		// If the player is flying, move them based on velocity without considering gravity
		if (!m_IsFlying && !m_IsGrounded && !World::Get()->GetPaused()) {
			ApplyGravity();
		}

		// Handle player input
		if (HandleInput())
			return;

		if (!m_AttackCooldown) {
			if (m_IsAttacking)
				Attack();
		}
		else
			m_AttackCooldown = std::max(0.0f, m_AttackCooldown - deltaTime);

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