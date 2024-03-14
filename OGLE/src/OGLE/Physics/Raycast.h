#pragma once

namespace OGLE
{
	class Raycast
	{
		friend class AABB;
		glm::vec3 m_Start;
		glm::vec3 m_Direction;
		glm::vec3 m_End;

	public:
		Raycast(glm::vec3 start, glm::vec3 direction, glm::vec3 end)
			: m_Start(start), m_Direction(direction), m_End(end) {}

		Raycast(glm::vec3 start, glm::vec3 direction, float distance)
			: Raycast(start, direction, start + direction * distance) {}

		std::vector<glm::vec3> GetVectors() { return { m_Start, m_Direction, m_End }; }
	};
}