#include "oglepch.h"
#include "OGLE/Buffer/OldBuffer.h"


namespace OGLE {

	void OldBuffer::SetData(GLsizeiptr size, const GLvoid* data)
	{
		m_Size = size;
		m_Data = data;
		AllocateBuffer();
	}

	void OldBuffer::InitBuffer()
	{
		GLCall(glGenBuffers(1, &m_BufferID)); 
		//PrintInitialized();
	}

	void OldBuffer::AllocateBuffer()
	{
		Bind(); 
		BufferData(); 
		//PrintStatus("Data Buffered");
		Unbind();
	}

	void OldBuffer::BufferData() const
	{
		GLCall(glBufferData(m_BufferTarget, m_Size, m_Data, m_BufferUsage));
	}

	void OldBuffer::BufferSubData(GLintptr offset/*=0*/, GLsizeiptr size/*=0*/, const GLvoid* data/*=NULL*/)
	{
		if (offset + size > m_Size)
			ExtendBuffer(size);
		GLCall(glBufferSubData(m_BufferTarget, offset, size, data));
	}

	void OldBuffer::ExtendBuffer(GLsizeiptr additionalSize)
	{
		m_Size += additionalSize;
		BufferData();
	}

	OldBuffer::OldBuffer(const OldBuffer& other)
	{
		m_BufferID = other.m_BufferID;
		m_Size = other.m_Size;
		m_Data = other.m_Data;
		m_Prefix = other.m_Prefix;
		m_BufferTarget = other.m_BufferTarget;
		m_BufferUsage = other.m_BufferUsage;
		m_Resizable = other.m_Resizable;
	}

	OldBuffer::OldBuffer(GLenum bufferTarget, GLsizeiptr size, const GLvoid* data, const char* prefix /*= ""*/, GLenum bufferUsage /*= GL_STATIC_DRAW*/) 
		: m_BufferTarget(bufferTarget), m_Size(size), m_Data(data), m_BufferUsage(bufferUsage), m_Prefix(prefix)
	{
		InitBuffer();
		AllocateBuffer();
	}

	OldBuffer::~OldBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	void OldBuffer::PrintStatus(const char* status)
	{
		std::cout << m_Prefix << "Buffer (ID " << m_BufferID << "): " << status << std::endl;
	}

	void OldBuffer::PrintInitialized()
	{
		PrintStatus("Initialized");
	}

	void OldBuffer::PrintBindStatus()
	{
		PrintStatus((m_IsBound) ? "Bound" : "Unbound");
	}

	void OldBuffer::Bind()
	{
		if (m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, m_BufferID)); 
		m_IsBound = true; 
		//PrintBindStatus();
	}

	void OldBuffer::Unbind()
	{
		if (!m_IsBound)
			return;
		GLCall(glBindBuffer(m_BufferTarget, 0)); 
		m_IsBound = false; 
		//PrintBindStatus();
	}

	GLsizeiptr OldBuffer::GetSize() const
	{
		return m_Size;
	}

	void OldBuffer::UpdateData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		if (!m_Resizable) {
			OGLE_CORE_ASSERT(size > m_Size, "Size of data is greater than the buffer has allocated");
			OGLE_CORE_ASSERT(offset > m_Size, "Offset of data is greater than the buffer has allocated");
			OGLE_CORE_ASSERT(offset + size > m_Size, "Data provided overflowed the size allocation");
		}
		BufferSubData(offset, size, data);
	}

	void OldBuffer::ResetData(GLsizeiptr size, const GLvoid* data)
	{
		SetData(size, data);
	}


	OldVertexBuffer::OldVertexBuffer(VertexCollection& vertices)
		: OldBuffer(GL_ARRAY_BUFFER,
			vertices.GetSize(),
			vertices.GetData(),
			"Vertex ")
	{
		InitVertexBuffer(vertices.GetLayout());
	}

	OldVertexBuffer::OldVertexBuffer(VertexCollection& vertices, std::vector<glm::mat4>& instanceMatrices)
		: OldBuffer(GL_ARRAY_BUFFER,
			vertices.GetSize(),
			vertices.GetData(),
			"Vertex ") 
	{
		InitInstanceBuffer(instanceMatrices);
		InitVertexBuffer(vertices.GetLayout());
	}

	OldVertexBuffer::OldVertexBuffer(const OldVertexBuffer& other)
	: OldBuffer(other){

		*m_IBO = *other.m_IBO;
		InitInstanceCount();

		m_Stride = other.m_Stride;
		m_AttribCount = other.m_AttribCount;

		m_VertexAttributes = other.m_VertexAttributes;
	}



	void OldVertexBuffer::BindInstanceBuffer()
	{
		if (m_IBO) m_IBO->Bind();
	}

	void OldVertexBuffer::UnbindInstanceBuffer()
	{
		if (m_IBO) m_IBO->Unbind();
	}

	GLuint OldVertexBuffer::GetStride() const
	{
		return m_Stride;
	}

	GLuint OldVertexBuffer::GetAttribCount() const
	{
		return m_AttribCount;
	}

	std::unordered_map<GLuint, DataAttribute*> OldVertexBuffer::GetVertexAttributes()
	{
		return m_VertexAttributes;
	}

	OGLE::OldVertexBuffer::InstanceBuffer& OldVertexBuffer::GetInstanceBuffer()
	{
		return *m_IBO;
	}

	void OldVertexBuffer::InitInstanceBuffer(std::vector<glm::mat4> instanceMatrices)
	{
		m_IBO = new InstanceBuffer(instanceMatrices);
	}

	GLuint OldVertexBuffer::GetInstanceCount()
	{
		return m_InstanceCount;
	}

	bool OldVertexBuffer::CheckInstanced()
	{
		return m_IsInstanced;
	}

	void OldVertexBuffer::InitInstanceCount()
	{
		if (m_IBO)
			m_InstanceCount = m_IBO->GetInstanceCount(); 
		m_IsInstanced = m_InstanceCount > 1;
	}

	void OldVertexBuffer::AddVertexAttribute(DataAttributeType attribType, GLboolean normalized /*= GL_FALSE*/)
	{
		m_VertexAttributes[m_Stride] = GetNewDataAttribute(m_AttribCount++, attribType, normalized);
		m_Stride += m_VertexAttributes[m_Stride]->Size;
	}

	void OldVertexBuffer::InitVertexBuffer(DataLayout layout)
	{
		InitInstanceCount();
		for (DataAttributeInfo attribData : layout.AttributeData)
			AddVertexAttribute(attribData.m_ControlType, attribData.Normalized);
	}

	OldElementBuffer::OldElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType /*= GL_UNSIGNED_SHORT*/)
		: OldBuffer(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(GLushort)* indices.size(),
			indices.data(), "Element "),
		m_ElementCount(indices.size()), m_ElementDataType(elementDataType)
	{
	}

	OldElementBuffer::OldElementBuffer(const OldElementBuffer& other)
		: OldBuffer(other)
	{
		m_ElementCount = other.m_ElementCount;
		m_ElementDataType = other.m_ElementDataType;
	}

	GLuint OldElementBuffer::GetElementCount() const
	{
		return m_ElementCount;
	}

	GLenum OldElementBuffer::GetElementDataType() const
	{
		return m_ElementDataType;
	}

	OldVertexBuffer::InstanceBuffer::InstanceBuffer(std::vector<glm::mat4>& instanceMatrices)
		: m_InstanceCount(instanceMatrices.size()), OldBuffer(GL_ARRAY_BUFFER,
			sizeof(glm::mat4)* instanceMatrices.size(),
			instanceMatrices.data(), "Instance "){	}

	GLuint OldVertexBuffer::InstanceBuffer::GetInstanceCount()
	{
		return m_InstanceCount;
	}

}