#include "oglepch.h"
#include "OGLE/Geometry/VertexArray.h"

namespace OGLE {

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

	void VertexArray::LinkVertexBufferToVertexArray()
	{
		
		Bind();
		SetVBOAttribPointers();
		Unbind();
	}

	void VertexArray::SetVBOAttribPointers()
	{	
		GLuint attributeIndex = 0;

		// Vertex Attributes
		BindVertexBuffer();
		std::unordered_map<GLuint, VertexAttribute*> vertexAttributes = m_VBO->GetVertexAttributes();
		VertexAttribute* vertexAttribute;
		for (GLuint offset = 0; offset < m_VBO->GetStride(); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(attributeIndex, vertexAttribute->Count, vertexAttribute->Type, vertexAttribute->Normalized, m_VBO->GetStride(), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(attributeIndex++));
			//std::cout << std::endl;
			//PrintStatus("AttribPointer set:");
			//std::cout << " - Index: " << attributeIndex - 1 << "\n - Number of elements in attribute: " << vertexAttribute->Count << "\n - Normalized: " << vertexAttribute->Normalized << "\n - Stride: " << m_VBO->GetStride() << "\n - offset: " << offset << "\n - Attribute Size: " << vertexAttribute->Size << std::endl;
			offset += vertexAttribute->Size;
		}
		UnbindVertexBuffer();

		// Matrix Attributes		
		if (m_VBO->CheckInstanced()) {
			BindInstanceBuffer();
			for (GLuint offset = 0; offset < sizeof(glm::mat4); offset += sizeof(glm::vec4))
			{

				GLCall(glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)offset));
				GLCall(glEnableVertexAttribArray(attributeIndex));
				GLCall(glVertexAttribDivisor(attributeIndex++, 1));
			}
			UnbindInstanceBuffer();
		}
	}

	void VertexArray::LinkElementBufferToVertexArray()
	{
		Bind();
		BindElementBuffer();
		Unbind();
	}

}