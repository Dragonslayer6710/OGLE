#include "oglepch.h"
#include "OGLE/Renderer/VertexArray.h"

namespace OGLE {

	VertexBuffer* VertexArray::GetVertexBuffer()
	{
		return m_VBO;
	}

	void VertexArray::SetVertexBuffer(VertexBuffer& vbo)
	{
		Bind();
		m_VBO = &vbo;
		SetAttribPointers();
		Unbind();
	}

	void VertexArray::SetAttribPointers()
	{
		m_VBO->Bind();
		GLuint i = 0;
		std::unordered_map<GLuint, VertexAttribute*> vertexAttributes = m_VBO->GetAttributes();
		VertexAttribute* vertexAttribute;
		for (GLuint offset = 0; offset < m_VBO->GetStride(); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(i, vertexAttribute->Count, vertexAttribute->Type, vertexAttribute->Normalized, m_VBO->GetStride(), (void*)offset));
			GLCall(glEnableVertexAttribArray(i++));
			offset += vertexAttribute->Size;
		}
		m_VBO->Unbind();
	}


	void VertexArray::SetElementBuffer(ElementBuffer& vbo)
	{
		Bind();
		m_EBO = &vbo;
		m_EBO->Bind();
		Unbind();
	}

}