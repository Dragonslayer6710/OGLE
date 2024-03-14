#include "oglepch.h"
#include "OGLE/Display/Renderer/Camera.h"
namespace OGLE {

	Camera::Camera(Ref<glm::vec3> position) : m_Position(position), m_Orientation(CreateRef<glm::vec3>(0.0f, 0.0f, -1.0f)), m_Up(CreateRef<glm::vec3>(0.0f, 1.0f, 0.0f))
	{

	}

	void Camera::Rotate()
	{
		glm::vec3 rotY = glm::cross(*m_Orientation, *m_Up);
		glm::vec3 newOrientation = glm::rotate(*m_Orientation, glm::radians(-(float)s_MouseDeltaY * m_CameraSensitivity), rotY);
		if (abs(glm::angle(newOrientation, *m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			*m_Orientation = newOrientation;
		glm::mat4 rotation = glm::rotate(glm::radians(-(float)s_MouseDeltaX * m_CameraSensitivity), *m_Up);
		*m_Orientation = glm::mat3(rotation) * *m_Orientation;
	}

	Ref<glm::vec3> Camera::GetPosition()
	{
		return m_Position;
	}

	Ref<glm::vec3> Camera::GetOrientation()
	{
		return m_Orientation;
	}

	Ref<glm::vec3> Camera::GetUp()
	{
		return m_Up;
	}

	Raycast Camera::GetRaycast(float distance)
	{
		return Raycast(*m_Position, glm::normalize(*m_Orientation), distance);
	}
}