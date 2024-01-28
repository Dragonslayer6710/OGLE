#include "oglepch.h"
#include "OGLE/Display/Renderer/Camera.h"
namespace OGLE {

	Camera::Camera(glm::vec2 initMousePos) : m_Pos(0.0f, 0.0f, 0.0f), m_Orientation(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f)
	{

	}

	bool Camera::IsControlBound()
	{
		return m_ControlEnabled;
	}

	void Camera::EnablControls()
	{
		m_ControlEnabled = true;
	}

	void Camera::DisableControls()
	{
		m_ControlEnabled = false;
	}

	void Camera::Rotate()
	{
		glm::vec3 rotY = glm::cross(m_Orientation, m_Up);
		glm::mat4 rotation =
			glm::rotate(glm::radians(-s_MouseDelta.x * m_CameraSensitivity), m_Up) *
			glm::rotate(glm::radians(-s_MouseDelta.y * m_CameraSensitivity), rotY);
		m_Orientation = glm::mat3(rotation) * m_Orientation;
	}

	void Camera::MoveForward()
	{
		m_Pos += m_MoveSpeed * m_Orientation;
	}

	void Camera::MoveBackward()
	{
		m_Pos -= m_MoveSpeed * m_Orientation;
	}

	void Camera::StrafeLeft()
	{
		m_Pos -= m_MoveSpeed * glm::cross(m_Orientation, m_Up);
	}

	void Camera::StrafeRight()
	{
		m_Pos += m_MoveSpeed * glm::cross(m_Orientation, m_Up);
	}

	void Camera::MoveUp()
	{
		m_Pos += m_MoveSpeed * m_Up;
	}

	void Camera::MoveDown()
	{
		m_Pos -= m_MoveSpeed * m_Up;
	}

	glm::mat4 Camera::GetWorldToViewMatrix() const
	{
		return glm::lookAt(m_Pos, m_Pos + m_Orientation, m_Up);
	}

}