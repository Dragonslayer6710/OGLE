#pragma once
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh(VertexCollection vertices, std::vector<GLushort> indices);
		VertexArray& GetVAO() { return *m_VAO; }
	protected:
		Mesh(VertexBuffer* vbo, ElementBuffer* ebo);
		void InitVAO();

	private:
		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;
		VertexArray* m_VAO;
	};

	class InstancedMesh : public Mesh
	{
	public:
		InstancedMesh(VertexCollection vertices, std::vector<GLushort> indices, InstanceDataCollection instanceData);
	};

}
