#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace OGLE {

	class Camera {
	public:

		Camera()
			: m_Pos(0.0f, 0.0f, 0.0f), m_Orientation(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f)
		{

		}

		glm::mat4 GetWorldToViewMatrix() const { return glm::lookAt(m_Pos, m_Pos + m_Orientation, m_Up); }
	public:
		glm::vec3 m_Pos;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;
	};
}
