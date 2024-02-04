#include "oglepch.h"
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {

	Mesh::Mesh(VertexCollection vertices, std::vector<GLushort> indices, InstanceDataCollection* instanceData /*= nullptr*/, Texture* texture /*= nullptr*/)
		: m_EBO(new ElementBuffer(indices)), m_Texture(texture)
	{
		if (instanceData != nullptr)
			m_VBO = new VertexBuffer(vertices, *instanceData);
		else
			m_VBO = new VertexBuffer(vertices);
		InitVAO();
	}

	void Mesh::InitVAO()
	{
		m_VAO = new VertexArray(*m_VBO, *m_EBO);
	}

}