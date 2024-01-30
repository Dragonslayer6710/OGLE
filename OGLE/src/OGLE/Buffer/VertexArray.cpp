#include "oglepch.h"
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE {

	VertexArray::VertexArray(VertexBuffer& vbo, ElementBuffer& ebo)
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
		return m_VBO->GetInstanceCount();
	}

	bool VertexArray::CheckInstanced()
	{
		return  m_VBO->CheckInstanced();
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

	void VertexArray::BindInstanceBuffer()
	{
		m_VBO->BindInstanceBuffer();
	}

	void VertexArray::UnbindInstanceBuffer()
	{
		m_VBO->UnbindInstanceBuffer();
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
			GLCall(glVertexAttribPointer(attributeIndex, vertexAttribute->Count, vertexAttribute->m_ControlType, vertexAttribute->Normalized, m_VBO->GetStride(), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(attributeIndex++));
			//std::cout << std::endl;
			//PrintStatus("AttribPointer set:");
			//std::cout << " - Index: " << attributeIndex - 1 << "\n - Number of elements in attribute: " << vertexAttribute->Count << "\n - Normalized: " << vertexAttribute->Normalized << "\n - Stride: " << m_VBO->GetStride() << "\n - offset: " << offset << "\n - Attribute Size: " << vertexAttribute->Size << std::endl;
			offset += vertexAttribute->Size;
		}
		UnbindVertexBuffer();

		// Matrix Attributes		
		if (CheckInstanced()) {
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