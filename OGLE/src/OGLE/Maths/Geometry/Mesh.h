#pragma once
#include "OGLE/Buffer/VertexArray.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh(VertexCollection* vertices, std::vector<GLushort>* indices, InstanceDataCollection* instanceData = nullptr);
		Mesh(const VertexCollection vertices, const std::vector<GLushort> indices, InstanceDataCollection* instanceData = nullptr);

		VertexArray& GetVAO() { return *m_VAO; }
	private:
		VertexArray* m_VAO;
	};
}
