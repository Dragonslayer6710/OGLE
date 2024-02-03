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

	VertexBuffer::VertexBuffer(VertexCollection& vertices, InstanceDataCollection& instanceData, GLenum bufferUsage /*= GL_STATIC_DRAW*/) :
		m_InstanceCount(instanceData.GetLength()),
		m_VertexCollection(&vertices),
		m_InstanceDataCollection(&instanceData),
		Buffer
		(
			GL_ARRAY_BUFFER,
			vertices.GetSize() + instanceData.GetSize(),
			NULL,
			bufferUsage
		)
	{

		// Set Vertex Data
		Bind();
		SetData(0, vertices.GetSize(), vertices.GetData());
		SetData(vertices.GetSize(), instanceData.GetSize(), instanceData.GetData());
		
		Unbind();
	}

	VertexBuffer::VertexBuffer(VertexCollection& vertices, GLenum bufferUsage /*= GL_STATIC_DRAW*/) :
		m_InstanceCount(1),
		m_VertexCollection(&vertices),
		m_InstanceDataCollection(nullptr),
		Buffer
		(
			GL_ARRAY_BUFFER,
			vertices.GetSize(),
			vertices.GetData(),
			bufferUsage
		)
	{

	}

	GLuint VertexBuffer::GetInstanceCount()
	{
		return m_InstanceCount;
	}

	std::unordered_map<GLuint, DataAttribute*> VertexBuffer::GetVertexAttributes()
	{

		return m_VertexCollection->GetAttributes();
	}


	GLuint VertexBuffer::GetVertexDataSize()
	{
		return m_VertexCollection->GetSize();
	}

	GLuint VertexBuffer::GetInstanceDataSize()
	{
		return m_InstanceDataCollection->GetSize();
	}

	std::unordered_map<GLuint, DataAttribute*> VertexBuffer::GetInstanceDataAttributes()
	{
		return m_InstanceDataCollection->GetAttributes();
	}


	ElementBuffer::ElementBuffer(std::vector<GLushort>& indices, GLenum bufferTarget, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/) : Buffer
	(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLushort)* indices.size(),
		indices.data(),
		bufferTarget
	),
		m_ElementCount(indices.size()),
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