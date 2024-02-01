#include "oglepch.h"
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE {

	VertexArray::VertexArray(VertexBuffer& vbo, ElementBuffer& ebo)
		: m_InstanceCount(vbo.GetInstanceCount())
	{
		InitVertexArray(vbo, ebo);
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_VertexArrayID));
	}

	void VertexArray::PrintStatus(const char* status)
	{
		std::cout << "Vertex Array (ID " << m_VertexArrayID << "): " << status << std::endl;
	}

	void VertexArray::PrintInitialized()
	{
		PrintStatus("Initialized");
	}

	void VertexArray::PrintBindStatus()
	{
		PrintStatus((m_IsBound) ? "Bound" : "Unbound");
	}

	void VertexArray::Bind()
	{
		if (m_IsBound)
			return;
		GLCall(glBindVertexArray(m_VertexArrayID));
		m_IsBound = true;
		//PrintBindStatus();		
	}

	void VertexArray::Unbind()
	{
		if (!m_IsBound)
			return;		
		GLCall(glBindVertexArray(0)); 
		m_IsBound = false; 
		//PrintBindStatus();
	}

	OGLE::VertexBuffer* VertexArray::GetVertexBuffer()
	{
		return m_VBO;
	}

	OGLE::ElementBuffer* VertexArray::GetElementBuffer()
	{
		return m_EBO;
	}

	GLuint VertexArray::GetElementCount()
	{
		return m_EBO->GetElementCount();
	}

	GLenum VertexArray::GetElementDataType()
	{
		return m_EBO->GetElementDataType();
	}

	GLuint VertexArray::GetInstanceCount()
	{
		return m_InstanceCount;
	}

	void VertexArray::InitVertexArray(VertexBuffer& vbo, ElementBuffer& ebo)
	{
		GLCall(glGenVertexArrays(1, &m_VertexArrayID));
		//PrintInitialized();

		m_RetainBind = true;
		Bind();
		LinkNewVertexBufferToVertexArray(vbo);
		LinkNewElementBufferToVertexArray(ebo);
		Unbind();
		m_RetainBind = false;
	}

	void VertexArray::LinkNewVertexBufferToVertexArray(VertexBuffer& vbo)
	{
		SetVertexBuffer(vbo); LinkVertexBufferToVertexArray();
	}

	void VertexArray::SetVertexBuffer(VertexBuffer& vbo)
	{
		m_VBO = &vbo;
	}

	void VertexArray::LinkVertexBufferToVertexArray()
	{
		
		Bind();
		SetVBOAttribPointers();
		Unbind();
	}

	void VertexArray::BindVertexBuffer()
	{
		m_VBO->Bind();
	}

	void VertexArray::UnbindVertexBuffer()
	{
		m_VBO->Unbind();
	}

	void VertexArray::SetVBOAttribPointers()
	{	
		GLuint attributeIndex = 0;

		BindVertexBuffer();
		// Vertex Attributes
		std::unordered_map<GLuint, DataAttribute*> vertexAttributes = m_VBO->GetVertexAttributes();
		DataAttribute* vertexAttribute;
		for (GLuint offset = 0; offset < m_VBO->GetVertexStride(); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(attributeIndex, vertexAttribute->Count, vertexAttribute->m_ControlType, vertexAttribute->Normalized, m_VBO->GetVertexStride(), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(attributeIndex++));
			//std::cout << std::endl;
			//PrintStatus("AttribPointer set:");
			std::cout << " - Index: " << attributeIndex - 1 << "\n - Number of elements in attribute: " << vertexAttribute->Count << "\n - Normalized: " << vertexAttribute->Normalized << "\n - Stride: " << m_VBO->GetVertexStride() << "\n - offset: " << offset << "\n - Attribute Size: " << vertexAttribute->Size << std::endl;
			offset += vertexAttribute->Size;
		}

		// Instance Data Attributes				
		if (m_InstanceCount>1) {
			std::unordered_map<GLuint, DataAttribute*> instanceDataAttributes = m_VBO->GetInstanceDataAttributes();
			DataAttribute* instanceDataAttribute;
			for (GLuint offset = 0; offset < m_VBO->GetInstanceDataStride(); offset)
			{
				instanceDataAttribute = instanceDataAttributes[offset];
				if (instanceDataAttribute->Count > 4)
					for (GLuint attribCount = instanceDataAttribute->Count; attribCount > 0; attribCount) {
						if (attribCount > 4) {
							GLCall(glVertexAttribPointer(attributeIndex, 4, instanceDataAttribute->m_ControlType, instanceDataAttribute->Normalized, m_VBO->GetInstanceDataStride(), (GLvoid*)offset));
							attribCount -= 4;
							std::cout << " - Index: " << attributeIndex  << "\n - Number of elements in attribute: " << 4 << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << m_VBO->GetInstanceDataStride() << "\n - offset: " << offset << "\n - Attribute Size: " << instanceDataAttribute->Size << std::endl;
							offset += instanceDataAttribute->Size / instanceDataAttribute->Count * 4;
						}
						else {
							GLCall(glVertexAttribPointer(attributeIndex, attribCount, instanceDataAttribute->m_ControlType, instanceDataAttribute->Normalized, m_VBO->GetInstanceDataStride(), (GLvoid*)offset));
							std::cout << " - Index: " << attributeIndex  << "\n - Number of elements in attribute: " << attribCount << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << m_VBO->GetInstanceDataStride() << "\n - offset: " << offset << "\n - Attribute Size: " << instanceDataAttribute->Size << std::endl;
							offset += instanceDataAttribute->Size / instanceDataAttribute->Count * attribCount;
							attribCount = 0;
						}
						GLCall(glEnableVertexAttribArray(attributeIndex));
						GLCall(glVertexAttribDivisor(attributeIndex++, 1));
					}
				else {
					GLCall(glVertexAttribPointer(attributeIndex, instanceDataAttribute->Count, instanceDataAttribute->m_ControlType, instanceDataAttribute->Normalized, m_VBO->GetInstanceDataStride(), (GLvoid*)offset));
					GLCall(glEnableVertexAttribArray(attributeIndex));
					GLCall(glVertexAttribDivisor(attributeIndex++, 1));
					std::cout << " - Index: " << attributeIndex  << "\n - Number of elements in attribute: " << instanceDataAttribute->Count << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << m_VBO->GetInstanceDataStride() << "\n - offset: " << offset << "\n - Attribute Size: " << instanceDataAttribute->Size << std::endl;
					offset += instanceDataAttribute->Size;
				}
			}
		}
		UnbindVertexBuffer();

	}

	void VertexArray::LinkNewElementBufferToVertexArray(ElementBuffer& ebo)
	{
		SetElementBuffer(ebo); LinkElementBufferToVertexArray();
	}

	void VertexArray::SetElementBuffer(ElementBuffer& ebo)
	{
		m_EBO = &ebo;
	}

	void VertexArray::LinkElementBufferToVertexArray()
	{
		Bind();
		BindElementBuffer();
		Unbind();
	}

	void VertexArray::BindElementBuffer()
	{
		m_EBO->Bind();
	}

	void VertexArray::UnbindElementBuffer()
	{
		m_EBO->Unbind();
	}

}