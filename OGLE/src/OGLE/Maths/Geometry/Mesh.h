#pragma once
#include "OGLE/Buffer/VertexArray.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh(VertexCollection vertices, std::vector<GLushort> indices, InstanceDataCollection* instanceData = nullptr, Texture* texture = nullptr);
		VertexArray& GetVAO() { return *m_VAO; }
	protected:
		void InitVAO();

	private:
		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;
		VertexArray* m_VAO;

		Texture* m_Texture;
	};
}
