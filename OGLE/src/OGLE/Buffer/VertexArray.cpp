#include "oglepch.h"
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE {

	VertexArray::VertexArray(VertexBufferData& vertexBufferData, std::vector<GLushort>& indices)
		: m_VBO(new VertexBuffer(vertexBufferData)), m_EBO(new ElementBuffer(&indices))
	{
		GLCall(glGenVertexArrays(1, &m_VertexArrayID));
		//PrintInitialized();

		Bind();

		// Bind VBO to VAO and init attrib pointers
		m_VBO->Bind();
		SetVertexDataPointers();
		if (m_VBO->IsInstanced())
			SetInstanceDataPointers();
		m_VBO->Unbind();

		//Bind EBO to VAO
		m_EBO->Bind();

		Unbind();
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
		return m_VBO->GetInstanceCount();
	}

	void VertexArray::SetVertexDataPointers()
	{
		std::unordered_map<GLuint, DataAttribute*> vertexAttributes = m_VBO->GetVertexAttributes();
		DataAttribute* vertexAttribute;
		for (GLuint offset = 0; offset < sizeof(VertexData); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(vertexAttribute->AttribID, vertexAttribute->Count, vertexAttribute->Type, vertexAttribute->Normalized, sizeof(VertexData), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(vertexAttribute->AttribID));
			glm::vec4 v4;
			glGetBufferSubData(GL_ARRAY_BUFFER, offset, 16, &v4);
			OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: ({2}, {3}, {4}, {5})\n", vertexAttribute->AttribID, offset, v4.x, v4.y, v4.z, v4.w);
			offset += vertexAttribute->Size;
		}
	}

	void VertexArray::SetInstanceDataPointers()
	{				
		std::unordered_map<GLuint, DataAttribute*> instanceDataAttributes = m_VBO->GetInstanceDataAttributes();
		GLuint offset;
		DataAttribute* instanceDataAttribute;
		for (GLuint offset = m_VBO->GetVertexDataSize(); offset < m_VBO->GetVertexDataSize()+sizeof(InstanceData); offset)
		{
			instanceDataAttribute = instanceDataAttributes[offset];
			if (instanceDataAttribute->Count > 4) {
				GLuint idOffset = 0;
				for (GLuint attribCount = instanceDataAttribute->Count; attribCount > 0; attribCount) {
					GLuint offsetAddition, count;
					if (attribCount > 4) {
						GLCall(glVertexAttribPointer(instanceDataAttribute->AttribID + idOffset, 4, instanceDataAttribute->Type, instanceDataAttribute->Normalized, sizeof(InstanceData), (GLvoid*)offset));
						count = 4;
						offsetAddition = instanceDataAttribute->Size / instanceDataAttribute->Count * 4;
					}
					else {
						GLCall(glVertexAttribPointer(instanceDataAttribute->AttribID + idOffset, attribCount, instanceDataAttribute->Type, instanceDataAttribute->Normalized, sizeof(InstanceData), (GLvoid*)offset));
						offsetAddition = instanceDataAttribute->Size / instanceDataAttribute->Count * attribCount;
						count = attribCount;
					}
					glm::vec4 v4;
					glGetBufferSubData(GL_ARRAY_BUFFER, offset, 16, &v4);
					OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: ({2}, {3}, {4}, {5})\n", instanceDataAttribute->AttribID + idOffset, offset, v4.x, v4.y, v4.z, v4.w);
					GLCall(glEnableVertexAttribArray(instanceDataAttribute->AttribID + idOffset));
					GLCall(glVertexAttribDivisor(instanceDataAttribute->AttribID + idOffset, 1));
					attribCount -= count;
					offset += offsetAddition;
					idOffset++;
					//std::cout << " - Index: " << attributeIndex-1 << "\n - Number of elements in attribute: " << count << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << sizeof(InstanceData) << "\n - offset: " << instOffset << "\n - Attribute Size: " << offsetAddition << std::endl;
				}
			}
			else {
				if (instanceDataAttribute->Type == UShort) {
					GLCall(glVertexAttribIPointer(instanceDataAttribute->AttribID, instanceDataAttribute->Count, instanceDataAttribute->Type, sizeof(InstanceData), (GLvoid*)offset));

					GLuint ui;
					glGetBufferSubData(GL_ARRAY_BUFFER, offset, 4, &ui);
					OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: {2}\n", instanceDataAttribute->AttribID, offset, ui);

					GLCall(glEnableVertexAttribArray(instanceDataAttribute->AttribID));
					GLCall(glVertexAttribDivisor(instanceDataAttribute->AttribID, 1));

					//std::cout << " - Index: " << attributeIndex-1  << "\n - Number of elements in attribute: " << instanceDataAttribute->Count << "\n - Normalized: " << instanceDataAttribute->Normalized << "\n - Stride: " << sizeof(InstanceData) << "\n - offset: " << instOffset << "\n - Attribute Size: " << instanceDataAttribute->Size << std::endl;
				}
				else {
					GLCall(glVertexAttribPointer(instanceDataAttribute->AttribID, instanceDataAttribute->Count, instanceDataAttribute->Type, instanceDataAttribute->Normalized, sizeof(InstanceData), (GLvoid*)offset));
					GLCall(glEnableVertexAttribArray(instanceDataAttribute->AttribID));
					GLCall(glVertexAttribDivisor(instanceDataAttribute->AttribID, 1));

					glm::vec2 v2;
					glGetBufferSubData(GL_ARRAY_BUFFER, offset, 8, &v2);
					OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: ({2}, {3})\n", instanceDataAttribute->AttribID, offset, v2.x, v2.y);
				}
				offset += instanceDataAttribute->Size;
			}
		}	
			
	}

}