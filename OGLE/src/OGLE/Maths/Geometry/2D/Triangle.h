#pragma once

#include "OGLE/Maths/Geometry/Drawable.h"
namespace OGLE {

	static std::vector<VertexData> s_TriangleVertices =
	{
		{glm::vec2(-0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)},
		{glm::vec2(-0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)},
		{glm::vec2(-0.75f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)},
	};


	static std::vector<GLushort> s_TriangleIndices =
	{
		0, 1, 2,
		//0, 3, 2
	};

	class Triangle : public Drawable
	{
	public:
		Triangle()
			: Drawable(new Mesh(s_TriangleVertices, s_TriangleIndices), nullptr){}
	};
}

