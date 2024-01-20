#include "oglepch.h"
#include "OGLE/Renderer/Buffer.h"


namespace OGLE {

	void Buffer::SetData(void* data, GLuint size)
	{
		Bind();
		m_Size = size;
		GLCall(glBufferData(m_BufferTarget, size, data, m_BufferUsage));
		Unbind();
	}

	void Buffer::UpdateData(void* data, GLuint size)
	{
		SetData(data, size);
	}


	void VertexBuffer::AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized /*= GL_FALSE*/)
	{
		m_VertexAttributes[m_Stride] = GetNewVertexAttribute(m_AttribCount, attribType, normalized);
		m_Stride += m_VertexAttributes[m_Stride]->Size;
	}

}