#pragma once
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE{

	class Shape
	{
	public:
		Shape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, GLuint instances=1)
			: m_Vertices(&vertices), m_Indices(&indices) { InitShape(); }
		Shape(const Shape& other);
		Shape(const Shape& other, std::vector<glm::mat4>& instanceMatrices);

		std::vector<Vertex>& GetVertices() { return *m_Vertices; }
		std::vector <GLushort>& GetIndices() { return *m_Indices; }

		VertexBuffer& GetVBO() { return *m_VBO; }
		ElementBuffer& GetEBO() { return *m_EBO; }
		VertexArray& GetVAO() { return *m_VAO; }
		
	private:
		void InitShape();

	protected:
		std::vector<Vertex>* m_Vertices;
		std::vector<GLushort>* m_Indices;
		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;
		VertexArray* m_VAO;
	};

	class InstancedShape : public Shape
	{
	public:
		InstancedShape(Shape& shape, std::vector<glm::mat4>& instanceMatrices) : m_InstanceMatrices(instanceMatrices), Shape(shape, instanceMatrices) {}

		InstancedShape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, std::vector<glm::mat4>& instanceMatrices)
			: m_InstanceMatrices(instanceMatrices), Shape(vertices, indices, m_InstanceMatrices.size()) {}
	protected:
		std::vector<glm::mat4> m_InstanceMatrices;
	};

}
