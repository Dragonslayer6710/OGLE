#include "oglepch.h"
#include "OGLE/Display/Renderer/Camera.h"
namespace OGLE {

	Camera::Camera() : m_Pos(0.0f, 0.0f, 0.0f), m_Orientation(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f)
	{

	}

	void Camera::Rotate()
	{
		glm::vec3 rotY = glm::cross(m_Orientation, m_Up);
		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-(float)s_MouseDeltaY * m_CameraSensitivity), rotY);
		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			m_Orientation = newOrientation;
		glm::mat4 rotation = glm::rotate(glm::radians(-(float)s_MouseDeltaX * m_CameraSensitivity), m_Up);
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

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(m_Pos, m_Pos + m_Orientation, m_Up);
	}

}