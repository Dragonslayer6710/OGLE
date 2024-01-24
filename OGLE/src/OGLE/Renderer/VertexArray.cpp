#include "oglepch.h"
#include "OGLE/Renderer/VertexArray.h"

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
		BindVertexBuffer();
		GLuint i = 0;
		std::unordered_map<GLuint, VertexAttribute*> vertexAttributes = m_VBO->GetAttributes();
		VertexAttribute* vertexAttribute;
		for (GLuint offset = 0; offset < m_VBO->GetStride(); offset)
		{
			vertexAttribute = vertexAttributes[offset];
			GLCall(glVertexAttribPointer(i, vertexAttribute->Count, vertexAttribute->Type, vertexAttribute->Normalized, m_VBO->GetStride(), (GLvoid*)offset));
			GLCall(glEnableVertexAttribArray(i++));
			//std::cout << std::endl;
			//PrintStatus("AttribPointer set:");
			std::cout << " - Index: " << i - 1 << "\n - Number of elements in attribute: " << vertexAttribute->Count << "\n - Normalized: " << vertexAttribute->Normalized << "\n - Stride: " << m_VBO->GetStride() << "\n - offset: " << offset << "\n - Attribute Size: " << vertexAttribute->Size << std::endl;
			offset += vertexAttribute->Size;
		}
		UnbindVertexBuffer();
	}

	void VertexArray::LinkElementBufferToVertexArray()
	{
		Bind();
		BindElementBuffer();
		Unbind();
	}

}