#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	static const std::initializer_list<Vertex> s_TriangleVertices
	{
		Vertex(glm::vec2(-0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)),
		Vertex(glm::vec2(-0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)),
		Vertex(glm::vec2(-0.75f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f))
	};

	static const std::vector<GLushort> s_TriangleIndices
	{
		0, 1, 2
	};

	class Triangle : public Shape
	{
	public:
		Ref<VertexCollection> NewVertexCollection() override
		{
			return Shape::NewVertexCollection(s_TriangleVertices, s_TriangleIndices);
		}
	};

	static const std::initializer_list<Vertex> s_QuadVertices
	{
		{ glm::vec2(-0.5, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2(-0.5, 0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec2(0.5, 0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(0.5,-0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f) }
	};

	static const std::vector<GLushort> s_QuadIndices
	{
		0, 1, 2,
		2, 3, 0
	};

	class Quad : public Shape
	{
	public:
		Ref<VertexCollection> NewVertexCollection() override
		{
			return Shape::NewVertexCollection(s_QuadVertices, s_QuadIndices);
		}
	};

}