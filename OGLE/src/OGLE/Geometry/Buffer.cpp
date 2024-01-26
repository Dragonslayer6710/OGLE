#include "oglepch.h"
#include "OGLE/Geometry/Buffer.h"


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
		if (offset + size > m_Size)
			ExtendBuffer(size);
		GLCall(glBufferSubData(m_BufferTarget, offset, size, data));
	}

	void Buffer::ExtendBuffer(GLsizeiptr additionalSize)
	{
		m_Size += additionalSize;
		BufferData();
	}

	Buffer::Buffer(const Buffer& other)
	{
		m_BufferID = other.m_BufferID;
		m_Size = other.m_Size;
		m_Data = other.m_Data;
		m_Prefix = other.m_Prefix;
		m_BufferTarget = other.m_BufferTarget;
		m_BufferUsage = other.m_BufferUsage;
		m_Resizable = other.m_Resizable;
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
		if (!m_Resizable) {
			OGLE_CORE_ASSERT(size > m_Size, "Size of data is greater than the buffer has allocated");
			OGLE_CORE_ASSERT(offset > m_Size, "Offset of data is greater than the buffer has allocated");
			OGLE_CORE_ASSERT(offset + size > m_Size, "Data provided overflowed the size allocation");
		}
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
		InitVertexBuffer(layout);
	}

	VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices, std::vector<glm::mat4>& instanceMatrices, VertexLayout layout /*= DefVertLayout*/)
		: Buffer(GL_ARRAY_BUFFER,
			sizeof(Vertex)* vertices.size(),
			vertices.data(),
			"Vertex ") 
	{
		SetInstanceBuffer(instanceMatrices);
		InitVertexBuffer(layout);
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& other)
	: Buffer(other){

		*m_IBO = *other.m_IBO;
		SetIntanceCount();

		m_Stride = other.m_Stride;
		m_AttribCount = other.m_AttribCount;

		m_VertexAttributes = other.m_VertexAttributes;
	}



	void VertexBuffer::SetInstanceBuffer(std::vector<glm::mat4> instanceMatrices)
	{
		m_IBO = new InstanceBuffer(*this, instanceMatrices);
	}

	void VertexBuffer::SetIntanceCount()
	{
		if (m_IBO)
			m_InstanceCount = m_IBO->GetInstanceCount(); 
		m_IsInstanced = m_InstanceCount > 1;
	}

	void VertexBuffer::AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized /*= GL_FALSE*/)
	{
		m_VertexAttributes[m_Stride] = GetNewVertexAttribute(m_AttribCount++, attribType, normalized);
		m_Stride += m_VertexAttributes[m_Stride]->Size;
	}

	void VertexBuffer::InitVertexBuffer(VertexLayout layout)
	{
		SetIntanceCount();
		for (VertexAttributeData attribData : *layout.AttributeData)
			AddVertexAttribute(attribData.Type, attribData.Normalized);
	}

	ElementBuffer::ElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/)
		: Buffer(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(GLushort)* indices.size(),
			indices.data(), "Element "),
		m_ElementCount(indices.size()), m_ElementDataType(elementDataType)
	{
	}

	ElementBuffer::ElementBuffer(const ElementBuffer& other)
		: Buffer(other)
	{
		m_ElementCount = other.m_ElementCount;
		m_ElementDataType = other.m_ElementDataType;
	}

	VertexBuffer::InstanceBuffer::InstanceBuffer(const VertexBuffer& vbo, std::vector<glm::mat4>& instanceMatrices)
		: m_InstanceCount(instanceMatrices.size()), Buffer(GL_ARRAY_BUFFER,
			sizeof(glm::mat4)* instanceMatrices.size(),
			instanceMatrices.data(), "Instance "){	}

}