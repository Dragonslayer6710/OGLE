#pragma once
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE{

	class Shape
	{
	public:
		Shape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, GLuint instances=1);
		Shape(const Shape& other);
		Shape(const Shape& other, std::vector<glm::mat4>& instanceMatrices);

		std::vector<Vertex>& GetVertices();
		std::vector <GLushort>& GetIndices();

		VertexBuffer& GetVBO();
		ElementBuffer& GetEBO();
		VertexArray& GetVAO();
		
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
		InstancedShape(Shape& shape, std::vector<glm::mat4>& instanceMatrices);

		InstancedShape(std::vector<Vertex>& vertices, std::vector<GLushort>& indices, std::vector<glm::mat4>& instanceMatrices);
	protected:
		std::vector<glm::mat4> m_InstanceMatrices;
	};

}
