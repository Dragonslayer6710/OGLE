#include "oglepch.h"
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	Buffer::Buffer(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum bufferUsage)
		:m_BufferTarget(target), m_Size(size), m_DataPtr(data), m_BufferUsage(bufferUsage)
	{
		GLCall(glGenBuffers(1, &m_BufferID));		
		InitBuffer();	
		Unbind();
	}

	Buffer::~Buffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	void Buffer::Bind()
	{
		GLCall(glBindBuffer(m_BufferTarget, m_BufferID));
	}

	void Buffer::Unbind()
	{
		GLCall(glBindBuffer(m_BufferTarget, 0));
	}

	void Buffer::SetData(GLintptr offset /*= 0*/, GLsizeiptr size /*= 0*/, const GLvoid* data /*= NULL*/)
	{
		BufferSubData(offset, size, data);
	}

	GLuint Buffer::GetSize()
	{
		return m_Size;
	}

	void Buffer::BufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		GLCall(glBufferSubData(m_BufferTarget, offset, size, data));
	}

	void Buffer::InitBuffer()
	{	
		Bind();
		BufferData(m_Size, m_DataPtr, m_BufferUsage);
	}

	void Buffer::BufferData(GLsizeiptr size, const GLvoid* data, GLenum bufferUsage /*= GL_STATIC_DRAW*/)
	{
		GLCall(glBufferData(m_BufferTarget, size, data, bufferUsage));
	}

	VertexBuffer::VertexBuffer(VertexBufferData& vertexBufferData, GLenum bufferUsage /*= GL_STATIC_DRAW*/) :
		m_VertexBufferData(vertexBufferData),
		Buffer
		(
			GL_ARRAY_BUFFER,
			vertexBufferData.GetSize(),
			NULL,
			bufferUsage
		),
		m_IsInstanced(m_VertexBufferData.IsInstanced())
	{

		// Set Vertex Data
		Bind();
		SetData(0, m_VertexBufferData.GetVDC().GetSize(), m_VertexBufferData.GetVDC().GetDataPtr());
		if (m_IsInstanced)
			SetData(m_VertexBufferData.GetVDC().GetSize(), m_VertexBufferData.GetIDC().GetSize(), m_VertexBufferData.GetIDC().GetDataPtr());		
		Unbind();
	}

	bool VertexBuffer::IsInstanced()
	{
		return m_IsInstanced;
	}

	std::unordered_map<GLuint, DataAttribute*> VertexBuffer::GetVertexAttributes()
	{

		return m_VertexBufferData.GetVDC().GetAttributes();
	}

	GLuint VertexBuffer::GetVertexDataSize()
	{
		return m_VertexBufferData.GetVDC().GetSize();
	}

	GLuint VertexBuffer::GetInstanceCount()
	{
		return m_VertexBufferData.GetIDC().GetLength();
	}

	GLuint VertexBuffer::GetInstanceDataSize()
	{
		return m_VertexBufferData.GetIDC().GetSize();
	}

	std::unordered_map<GLuint, DataAttribute*> VertexBuffer::GetInstanceDataAttributes()
	{
		return m_VertexBufferData.GetIDC().GetAttributes();
	}


	ElementBuffer::ElementBuffer(std::vector<GLushort>* indices, GLenum bufferTarget, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/) : Buffer
	(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLushort)* indices->size(),
		indices->data(),
		bufferTarget
	),
		m_ElementCount(indices->size()),
		m_ElementDataType(elementDataType)
	{

	}

	GLuint ElementBuffer::GetElementCount() const
	{
		return m_ElementCount;
	}

	GLenum ElementBuffer::GetElementDataType() const
	{
		return m_ElementDataType;
	}

}