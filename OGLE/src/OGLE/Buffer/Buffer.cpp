#include "oglepch.h"
#include "OGLE/Buffer/Buffer.h"


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

	Buffer::Buffer(GLenum bufferTarget, GLsizeiptr size, const GLvoid* data, const char* prefix /*= ""*/, GLenum bufferUsage /*= GL_STATIC_DRAW*/) 
		: m_BufferTarget(bufferTarget), m_Size(size), m_Data(data), m_BufferUsage(bufferUsage), m_Prefix(prefix)
	{
		InitBuffer();
		AllocateBuffer();
	}

	Buffer::~Buffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	void Buffer::PrintStatus(const char* status)
	{
		std::cout << m_Prefix << "Buffer (ID " << m_BufferID << "): " << status << std::endl;
	}

	void Buffer::PrintInitialized()
	{
		PrintStatus("Initialized");
	}

	void Buffer::PrintBindStatus()
	{
		PrintStatus((m_IsBound) ? "Bound" : "Unbound");
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

	GLsizeiptr Buffer::GetSize() const
	{
		return m_Size;
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
		InitInstanceBuffer(instanceMatrices);
		InitVertexBuffer(layout);
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& other)
	: Buffer(other){

		*m_IBO = *other.m_IBO;
		InitInstanceCount();

		m_Stride = other.m_Stride;
		m_AttribCount = other.m_AttribCount;

		m_VertexAttributes = other.m_VertexAttributes;
	}



	void VertexBuffer::BindInstanceBuffer()
	{
		if (m_IBO) m_IBO->Bind();
	}

	void VertexBuffer::UnbindInstanceBuffer()
	{
		if (m_IBO) m_IBO->Unbind();
	}

	GLuint VertexBuffer::GetStride() const
	{
		return m_Stride;
	}

	GLuint VertexBuffer::GetAttribCount() const
	{
		return m_AttribCount;
	}

	std::unordered_map<GLuint, VertexAttribute*> VertexBuffer::GetVertexAttributes()
	{
		return m_VertexAttributes;
	}

	OGLE::VertexBuffer::InstanceBuffer& VertexBuffer::GetInstanceBuffer()
	{
		return *m_IBO;
	}

	void VertexBuffer::InitInstanceBuffer(std::vector<glm::mat4> instanceMatrices)
	{
		m_IBO = new InstanceBuffer(instanceMatrices);
	}

	GLuint VertexBuffer::GetInstanceCount()
	{
		return m_InstanceCount;
	}

	bool VertexBuffer::CheckInstanced()
	{
		return m_IsInstanced;
	}

	void VertexBuffer::InitInstanceCount()
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
		InitInstanceCount();
		for (VertexAttributeData attribData : *layout.AttributeData)
			AddVertexAttribute(attribData.m_ControlType, attribData.Normalized);
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

	GLuint ElementBuffer::GetElementCount() const
	{
		return m_ElementCount;
	}

	GLenum ElementBuffer::GetElementDataType() const
	{
		return m_ElementDataType;
	}

	VertexBuffer::InstanceBuffer::InstanceBuffer(std::vector<glm::mat4>& instanceMatrices)
		: m_InstanceCount(instanceMatrices.size()), Buffer(GL_ARRAY_BUFFER,
			sizeof(glm::mat4)* instanceMatrices.size(),
			instanceMatrices.data(), "Instance "){	}

	GLuint VertexBuffer::InstanceBuffer::GetInstanceCount()
	{
		return m_InstanceCount;
	}

}