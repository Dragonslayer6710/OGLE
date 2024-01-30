#pragma once

#include "OGLE/Maths/Geometry/Shape/Shape.h"
namespace OGLE {

	static std::vector<Vertex> s_TriangleVertices =
	{
		Vertex{glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(-0.75f, -1.0f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
		//Vertex{glm::vec3( 0.0f, -0.5f,  0.0f), glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f)}
	};

	static std::vector<GLushort> s_TriangleIndices =
	{
		0, 1, 2,
		//0, 3, 2
	};

	class Triangle : public Shape
	{
	public:
		Triangle()
			: Shape(s_TriangleVertices, s_TriangleIndices) {}
	};
}

