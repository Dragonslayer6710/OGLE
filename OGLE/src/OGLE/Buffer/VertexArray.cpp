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

		for (GLuint offset = 0; offset < sizeof(Vertex); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(attributeIndex, vertexAttribute->Count, vertexAttribute->Type, vertexAttribute->Normalized, sizeof(Vertex), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(attributeIndex++));
			//std::cout << std::endl;
			//PrintStatus("AttribPointer set:");
			//std::cout << " - Index: " << attributeIndex - 1 << "\n - Number of elements in attribute: " << vertexAttribute->Count << "\n - Normalized: " << vertexAttribute->Normalized << "\n - Stride: " << sizeof(Vertex) << "\n - offset: " << offset << "\n - Attribute Size: " << vertexAttribute->Size << std::endl;
			offset += vertexAttribute->Size;
		}
		// Instance Data Attributes				
		if (m_InstanceCount>1) {
			GLuint instOffset = m_VBO->GetVertexDataSize();
			std::unordered_map<GLuint, DataAttribute*> instanceDataAttributes = m_VBO->GetInstanceDataAttributes();
			DataAttribute* instanceDataAttribute;
			for (GLuint offset = 0; offset <sizeof(InstanceData); offset)
			{
				instanceDataAttribute = instanceDataAttributes[offset];
				if (instanceDataAttribute->Count > 4) {
					for (GLuint attribCount = instanceDataAttribute->Count; attribCount > 0; attribCount) {
						GLuint offsetAddition, count;
						if (attribCount > 4) {
							GLCall(glVertexAttribPointer(attributeIndex, 4, instanceDataAttribute->Type, instanceDataAttribute->Normalized, sizeof(InstanceData), (GLvoid*)instOffset));
							count = 4;
							offsetAddition = instanceDataAttribute->Size / instanceDataAttribute->Count * 4;
						}
						else {
							GLCall(glVertexAttribPointer(attributeIndex, attribCount, instanceDataAttribute->Type, instanceDataAttribute->Normalized, sizeof(InstanceData), (GLvoid*)instOffset));
							offsetAddition = instanceDataAttribute->Size / instanceDataAttribute->Count * attribCount;
							count = attribCount;
						}
						glm::vec4 v4;
						glGetBufferSubData(GL_ARRAY_BUFFER, instOffset, 16, &v4);
						OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: ({2}, {3}, {4}, {5})\n", attributeIndex, instOffset, v4.x, v4.y, v4.z, v4.w);
						GLCall(glEnableVertexAttribArray(attributeIndex));
						GLCall(glVertexAttribDivisor(attributeIndex++, 1));
						attribCount -= count;
						offset += offsetAddition;
						//std::cout << " - Index: " << attributeIndex-1 << "\n - Number of elements in attribute: " << count << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << sizeof(InstanceData) << "\n - offset: " << instOffset << "\n - Attribute Size: " << offsetAddition << std::endl;
						instOffset += offsetAddition;
					}
				}
				else {
					GLCall(glVertexAttribIPointer(attributeIndex, instanceDataAttribute->Count, instanceDataAttribute->Type, sizeof(InstanceData), (GLvoid*)instOffset));
					GLuint ui;
					glGetBufferSubData(GL_ARRAY_BUFFER, instOffset, 4, &ui);
					OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: {2}\n", attributeIndex, instOffset, ui);
					//glGetBufferSubData(GL_ARRAY_BUFFER, instOffset + sizeof(InstanceData), 4, &ui);
					//OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: {2}\n", instOffset + sizeof(InstanceData), attributeIndex, ui);
					//glGetBufferSubData(GL_ARRAY_BUFFER, instOffset + sizeof(InstanceData)*2, 4, &ui);
					//OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: {2}\n", instOffset + sizeof(InstanceData) * 2, attributeIndex, ui);
					GLCall(glEnableVertexAttribArray(attributeIndex));
					GLCall(glVertexAttribDivisor(attributeIndex++, 1));
					GLuint i[4];
					glGetVertexAttribIuiv(7, GL_CURRENT_VERTEX_ATTRIB, i);
					//std::cout << " - Index: " << attributeIndex-1  << "\n - Number of elements in attribute: " << instanceDataAttribute->Count << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << sizeof(InstanceData) << "\n - offset: " << instOffset << "\n - Attribute Size: " << instanceDataAttribute->Size << std::endl;
					offset += instanceDataAttribute->Size;	
					instOffset += offset;
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