#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	static VertexList s_TriangleVertexList = VertexList(
		{
			Vertex(glm::vec2(-0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)),
			Vertex(glm::vec2(-0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)),
			Vertex(glm::vec2(-0.75f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f))
		}
	);

	static VertexCollection s_TriangleVertices = VertexCollection(s_TriangleVertexList, s_DefVertexLayout);


	static std::vector<GLushort> s_TriangleIndices =
	{
		0, 1, 2,
	};

	class Triangle : public Shape
	{
	public:
		Triangle
		(
			glm::vec3* position = new glm::vec3(0.0f),
			glm::vec3* rotDeg = new glm::vec3(0.0f),
			glm::vec3* scale = new glm::vec3(1.0f)
		)
			: Shape(s_TriangleVertices, s_TriangleIndices, position, rotDeg, scale) {}
	};
}

