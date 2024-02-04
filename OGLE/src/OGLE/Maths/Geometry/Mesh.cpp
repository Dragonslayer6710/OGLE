#include "oglepch.h"
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {

	Mesh::Mesh
	(
		std::vector<VertexData>& vertices,
		std::vector<GLushort>& indices,
		std::vector<InstanceData>* instanceData,
		DataLayout vertexLayout,
		DataLayout instanceDataLayout
	)
		: Mesh(new VertexBufferData(vertices, instanceData, vertexLayout, instanceDataLayout), indices)
	{}

	Mesh::Mesh(VertexBufferData* vertexBufferData, std::vector<GLushort>& indices)
		: m_VertexBufferData(*vertexBufferData)
	{
		m_VAO = new VertexArray(m_VertexBufferData, indices);
	}

}