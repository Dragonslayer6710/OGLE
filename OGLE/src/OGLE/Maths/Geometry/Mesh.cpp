#include "oglepch.h"
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {

	Mesh::Mesh(VertexCollection* vertices, std::vector<GLushort>* indices, InstanceDataCollection* instanceData /*= nullptr*/)
	{
		m_VAO = new VertexArray(vertices, indices, instanceData);
	}

	Mesh::Mesh(const VertexCollection vertices, const std::vector<GLushort> indices, InstanceDataCollection* instanceData /*= nullptr*/)
		: Mesh(new VertexCollection(vertices), new std::vector<GLushort>(indices), instanceData)
	{

	}

}