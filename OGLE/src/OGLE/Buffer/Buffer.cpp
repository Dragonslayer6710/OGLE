#include "oglepch.h"
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {
	//init buffer params
	Buffer::Buffer(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum bufferUsage)
		:m_BufferTarget(target), m_BufferUsage(bufferUsage)
	{
		// Generate buffer then bind
		GLCall(glGenBuffers(1, &m_BufferID));
		Bind();
		// 0 fill the buffer to the dedicated size and set data to buffer if provided
		GLCall(glBufferData(m_BufferTarget, size, data, bufferUsage));
		Unbind();
	}

	Buffer::~Buffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	bool Buffer::IsBound()
	{
		return m_IsBound;
	}

	void Buffer::Bind()
	{
		if (m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, m_BufferID));
		m_IsBound = true;
	}

	void Buffer::Unbind()
	{
		if (!m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, 0));
		m_IsBound = false;
	}

	void Buffer::SetData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		GLCall(glBufferSubData(m_BufferTarget, offset, size, data));
	}


	Ref<ElementBuffer> ElementBuffer::Create(std::vector<GLushort>* indices, GLenum bufferTarget /*= GL_STATIC_DRAW*/, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/)
	{
		return CreateRef<ElementBuffer>(indices, bufferTarget, elementDataType);
	}

	ElementBuffer::ElementBuffer(std::vector<GLushort>* indices, GLenum bufferTarget, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/) : Buffer
	(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLushort)* indices->size(),
		indices->data(),
		bufferTarget
	)
	{

	}



	Ref<VertexBuffer> VertexBuffer::Create(GLsizeiptr size, const GLvoid* data, GLenum bufferUsage /*= GL_STATIC_DRAW*/)
	{
		return CreateRef<VertexBuffer>(size, data, bufferUsage);
	}

}