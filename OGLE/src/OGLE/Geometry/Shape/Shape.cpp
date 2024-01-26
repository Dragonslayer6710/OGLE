#include "oglepch.h"
#include "OGLE/Geometry/Shape/Shape.h"

namespace OGLE {

	Shape::Shape(const Shape& other)
	{
		m_Vertices = other.m_Vertices;
		m_Indices = other.m_Indices;
		InitShape();
	}

	Shape::Shape(const Shape& other, std::vector<glm::mat4>& instanceMatrices)
	{
		delete other.m_VBO;
		delete other.m_VAO;
		m_Vertices = other.m_Vertices;
		m_Indices = other.m_Indices;
		m_VBO = new VertexBuffer(*m_Vertices, instanceMatrices);
		*m_EBO = *other.m_EBO;
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

	void Shape::InitShape()
	{
		m_VBO = new VertexBuffer(*m_Vertices);
		m_EBO = new ElementBuffer(*m_Indices);
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

}