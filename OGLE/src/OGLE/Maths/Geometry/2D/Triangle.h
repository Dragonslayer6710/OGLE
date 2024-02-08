#pragma once

#include "OGLE/Maths/Geometry/Mesh.h"
namespace OGLE {

	static VertexList s_TriangleVertices = VertexList(
		{
			Vertex(glm::vec2(-0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)),
			Vertex(glm::vec2(-0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)),
			Vertex(glm::vec2(-0.75f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f))
		}
	);


	static std::vector<GLushort> s_TriangleIndices =
	{
		0, 1, 2,
	};

	class Triangle : public Mesh
	{
	public:
		Triangle(InstanceList* instanceList = nullptr)
		:Mesh(s_TriangleVertices, s_TriangleIndices, instanceList){};
	};
}

