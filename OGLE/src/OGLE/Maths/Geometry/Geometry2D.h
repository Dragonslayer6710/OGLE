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

	class Cross : public Shape
	{
		float m_Thickness;
		glm::vec2 m_Translation;
		float m_Rotation;
		glm::vec2 m_Scale;

	public:
		static Scope<Cross> Create(float thickness = 1.0f, glm::vec2 translation = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 scale = glm::vec2(1.0f))
		{
			Scope<Cross> cross = CreateScope<Cross>(thickness, translation, rotation, scale);
			cross->SetVertexCollection();
			return cross;
		}

		Cross(float thickness = 1.0f, glm::vec2 translation = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 scale = glm::vec2(1.0f))
			: m_Thickness(thickness), m_Translation(translation), m_Rotation(rotation), m_Scale(scale) {}

		float GetThickness() { return m_Thickness; }

		Scope<VertexCollection> NewVertexCollection() override
		{
			std::array<Vertex, 4> crossVertices = {
				Vertex(glm::vec3(m_Translation + glm::rotate(glm::vec2{-0.05f,  0.00f } * m_Scale, glm::radians(m_Rotation)), 0.0f),	 glm::vec4{1.0f}, glm::vec2{0.0f, 0.0f}),
				Vertex(glm::vec3(m_Translation + glm::rotate(glm::vec2{ 0.05f,  0.00f } * m_Scale, glm::radians(m_Rotation)), 0.0f),	 glm::vec4{1.0f}, glm::vec2{0.0f, 0.0f}),
				Vertex(glm::vec3(m_Translation + glm::rotate(glm::vec2{ 0.00f, -0.05f } * m_Scale, glm::radians(m_Rotation)), 0.0f),	 glm::vec4{1.0f}, glm::vec2{0.0f, 0.0f}),
				Vertex(glm::vec3(m_Translation + glm::rotate(glm::vec2{ 0.00f,  0.05f } * m_Scale, glm::radians(m_Rotation)), 0.0f),	 glm::vec4{1.0f}, glm::vec2{0.0f, 0.0f})
			};
			std::array<GLushort, 4> crossIndices = { 0, 1, 2, 3};

			return Shape::NewVertexCollection<4, 4>(crossVertices, crossIndices);
		}
	};

	class Line : public Shape
	{
		glm::vec3 m_StartPos;
		glm::vec3 m_EndPos;

	public:
		static Scope<Line> Create(glm::vec3 start, glm::vec3 end)
		{
			Scope<Line> line = CreateScope<Line>(start, end);
			line->SetVertexCollection();
			return line;
		}

		Line(glm::vec3 start, glm::vec3 end) : m_StartPos(start), m_EndPos(end) {}

		glm::vec3 GetStartPosition() const { return m_StartPos; }
		glm::vec3 GetEndPosition() const { return m_EndPos; }

		Scope<VertexCollection> NewVertexCollection() override
		{
			std::array<Vertex, 2> lineVertices = {
				Vertex(m_StartPos, glm::vec4{1.0f}, glm::vec2{0.0f}),
				Vertex(m_EndPos, glm::vec4{1.0f}, glm::vec2{0.0f})
			};
			std::array<GLushort, 2> lineIndices = { 0, 1 };

			return Shape::NewVertexCollection<2, 2>(lineVertices, lineIndices);
		}
	};


}