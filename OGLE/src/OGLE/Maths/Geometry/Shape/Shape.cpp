#include "oglepch.h"
#include "OGLE/Maths/Geometry/Shape/Shape.h"

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

	Shape::Shape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, GLuint instances/*=1*/) : m_Vertices(&vertices), m_Indices(&indices)
	{
		if (instances == 1)
			InitShape();
	}

	std::vector<OGLE::Vertex>& Shape::GetVertices()
	{
		return *m_Vertices;
	}

	std::vector <GLushort>& Shape::GetIndices()
	{
		return *m_Indices;
	}

	OGLE::VertexBuffer& Shape::GetVBO()
	{
		return *m_VBO;
	}

	OGLE::ElementBuffer& Shape::GetEBO()
	{
		return *m_EBO;
	}

	OGLE::VertexArray& Shape::GetVAO()
	{
		return *m_VAO;
	}

	void Shape::InitShape()
	{
		m_VBO = new VertexBuffer(*m_Vertices);
		m_EBO = new ElementBuffer(*m_Indices);
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

	InstancedShape::InstancedShape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, std::vector<glm::mat4>& instanceMatrices)
		: m_InstanceMatrices(instanceMatrices), Shape(vertices, indices, m_InstanceMatrices.size())
	{
		m_VBO = new VertexBuffer(*m_Vertices, instanceMatrices);
		m_EBO = new ElementBuffer(*m_Indices);
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

	InstancedShape::InstancedShape(Shape& shape, std::vector<glm::mat4>& instanceMatrices) 
		: m_InstanceMatrices(instanceMatrices), Shape(shape, instanceMatrices)
	{
	}

}