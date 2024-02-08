#pragma once

#include "OGLE/Maths/Geometry/Mesh.h"
namespace OGLE {

	static VertexList s_QuadVertices = VertexList(
		{
			{ glm::vec2(-0.5,-0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec2(-0.5, 0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f) },
			{ glm::vec2(0.5, 0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec2(0.5,-0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f) }
		}
	);

	static std::vector<GLushort> s_QuadIndices = 
	{
		0, 1, 2,
		2, 3, 0
	};


	class Quad : public Mesh
	{
	public:
		Quad(InstanceList* instanceList = nullptr)
			: Mesh(s_QuadVertices, s_QuadIndices, instanceList) {}
	};
}