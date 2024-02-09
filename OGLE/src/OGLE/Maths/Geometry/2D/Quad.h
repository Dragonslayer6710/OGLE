#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	static VertexList s_QuadVertexList = VertexList(
		{
			{ glm::vec2(-0.5,-0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec2(-0.5, 0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f) },
			{ glm::vec2(0.5, 0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec2(0.5,-0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f) }
		}
	);

	static VertexCollection s_QuadVertices = VertexCollection(s_QuadVertexList, s_DefVertexLayout);

	static std::vector<GLushort> s_QuadIndices = 
	{
		0, 1, 2,
		2, 3, 0
	};


	class Quad : public Shape
	{
	public:
		Quad
		(
			glm::vec3* position = new glm::vec3(0.0f),
			glm::vec3* rotDeg = new glm::vec3(0.0f),
			glm::vec3* scale = new glm::vec3(1.0f)
		)
			: Shape(s_QuadVertices, s_QuadIndices, position, rotDeg, scale) {}
	};
}