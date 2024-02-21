#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	class Triangle : public Shape
	{
	public:
		Scope<VertexCollection> NewVertexCollection() override
		{
			constexpr std::array<Vertex, 3> triangleVertices = {
				Vertex(glm::vec3{-0.5f,  0.5f, 0.0f}, glm::vec4{0.5f, 0.0f, 0.0f, 0.5f}, glm::vec2{0.0f}),
				Vertex(glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{0.0f, 0.5f, 0.0f, 0.5f}, glm::vec2{0.0f}),
				Vertex(glm::vec3{-0.75f,-0.5f, 0.0f}, glm::vec4{0.0f, 0.0f, 0.5f, 0.5f}, glm::vec2{0.0f})
			};

			constexpr std::array<GLushort, 3> triangleIndices = { 0, 1, 2 };

			return Shape::NewVertexCollection<3, 3>(triangleVertices, triangleIndices);
		}
	};

	class Quad : public Shape
	{
	public:
		Scope<VertexCollection> NewVertexCollection() override
		{
			constexpr std::array<Vertex, 4> quadVertices = {
				Vertex(glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{1.0f}, glm::vec2{0.0f, 0.0f}),
				Vertex(glm::vec3{-0.5f,  0.5f, 0.0f}, glm::vec4{1.0f}, glm::vec2{0.0f, 1.0f}),
				Vertex(glm::vec3{ 0.5f,  0.5f, 0.0f}, glm::vec4{1.0f}, glm::vec2{1.0f, 1.0f}),
				Vertex(glm::vec3{ 0.5f, -0.5f, 0.0f}, glm::vec4{1.0f}, glm::vec2{1.0f, 0.0f})
			};

			constexpr std::array<GLushort, 6> quadIndices = { 0, 1, 2, 2, 3, 0 };

			return Shape::NewVertexCollection<4, 6>(quadVertices, quadIndices);
		}
	};

}