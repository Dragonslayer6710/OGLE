#pragma once
#include "OGLE/Buffer/VertexArray.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh
		(
			std::vector<VertexData>& vertices,
			std::vector<GLushort>& indices,
			std::vector<InstanceData>* instanceData = nullptr,
			DataLayout vertexLayout = s_DefVertexDataLayout,
			DataLayout instanceDataLayout = s_DefInstanceDataLayout
		);

		Mesh(VertexBufferData* vertexBufferData, std::vector<GLushort>& indices);

		VertexArray& GetVAO() { return *m_VAO; }
	private:

		VertexBufferData m_VertexBufferData;

		VertexArray* m_VAO;
	};
}
