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

	Scope<VertexBuffer> VertexBuffer::Create(Ref<Collection<Vertex>> collection, GLenum bufferUsage /*= GL_STATIC_DRAW*/)
	{
		return CreateScope<VertexBuffer>(collection, bufferUsage);
	}

	Scope<InstanceBuffer> InstanceBuffer::Create(Ref<Collection<Instance>> collection, GLenum bufferUsage /*= GL_STATIC_DRAW*/)
	{
		return CreateScope<InstanceBuffer>(collection, bufferUsage);
	}

}