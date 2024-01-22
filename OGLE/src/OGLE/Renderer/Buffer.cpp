#include "oglepch.h"
#include "OGLE/Renderer/Buffer.h"


namespace OGLE {

	void Buffer::SetData(GLsizeiptr size, const GLvoid* data)
	{
		m_Size = size;
		m_Data = data;
		AllocateBuffer();
	}

	void Buffer::InitBuffer()
	{
		GLCall(glGenBuffers(1, &m_BufferID)); 
		//PrintInitialized();
	}

	void Buffer::AllocateBuffer()
	{
		Bind(); 
		BufferData(); 
		//PrintStatus("Data Buffered");
		Unbind();
	}

	void Buffer::BufferData() const
	{
		GLCall(glBufferData(m_BufferTarget, m_Size, m_Data, m_BufferUsage));
	}

	void Buffer::BufferSubData(GLintptr offset/*=0*/, GLsizeiptr size/*=0*/, const GLvoid* data/*=NULL*/)
	{
		GLCall(glBufferSubData(m_BufferTarget, offset, size, data));
	}

	void Buffer::Bind()
	{
		if (m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, m_BufferID)); 
		m_IsBound = true; 
		//PrintBindStatus();
	}

	void Buffer::Unbind()
	{
		if (!m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, 0)); 
		m_IsBound = false; 
		//PrintBindStatus();
	}

	void Buffer::UpdateData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		OGLE_CORE_ASSERT(size > m_Size, "Size of data is greater than the buffer has allocated");
		OGLE_CORE_ASSERT(offset > m_Size, "Offset of data is greater than the buffer has allocated");
		BufferSubData(offset, size, data);
	}

	void Buffer::ResetData(GLsizeiptr size, const GLvoid* data)
	{
		SetData(size, data);
	}


	VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices, VertexLayout layout)
		: Buffer(GL_ARRAY_BUFFER,
			sizeof(Vertex) * vertices.size(),
			vertices.data(),
			"Vertex ")
	{
		for (VertexAttributeData attribData : *layout.AttributeData)
			AddVertexAttribute(attribData.Type, attribData.Normalized);
	}

	void VertexBuffer::AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized /*= GL_FALSE*/)
	{
		m_VertexAttributes[m_Stride] = GetNewVertexAttribute(m_AttribCount++, attribType, normalized);
		m_Stride += m_VertexAttributes[m_Stride]->Size;
	}

	ElementBuffer::ElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/) 
		: Buffer(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(GLushort)* indices.size(),
			indices.data(), "Element "),
		m_ElementCount(indices.size()), m_ElementDataType(elementDataType)
	{
	}

}