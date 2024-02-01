#include "oglepch.h"
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {

	Mesh::Mesh(VertexCollection vertices, std::vector<GLushort> indices)
		:m_VBO(new VertexBuffer(vertices)), m_EBO(new ElementBuffer(indices))
	{
		InitVAO();
	}

	Mesh::Mesh(VertexBuffer* vbo, ElementBuffer* ebo)
		: m_VBO(vbo), m_EBO(ebo)
	{
		InitVAO();
	}

	void Mesh::InitVAO()
	{
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

	InstancedMesh::InstancedMesh(VertexCollection vertices, std::vector<GLushort> indices, InstanceDataCollection instanceData)
		: Mesh(new VertexBuffer(vertices, instanceData), new ElementBuffer(indices))
	{
	}

}