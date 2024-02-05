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
		std::unordered_map<GLuint, DataAttribute*> vertexAttributes = m_VBO->GetVertexAttributes();
		for (GLuint offset = 0; offset < sizeof(Vertex); offset += vertexAttributes[offset]->Size)
			SetAttribPointer(vertexAttributes[offset], sizeof(Vertex), offset);

		if (m_VBO->IsInstanced())
		{
			std::unordered_map<GLuint, DataAttribute*> instanceDataAttributes = m_VBO->GetInstanceDataAttributes();
			for (GLuint offset = 0; offset < sizeof(Instance); offset += instanceDataAttributes[offset]->Size)
				SetAttribPointer(instanceDataAttributes[offset], sizeof(Instance), offset, m_VBO->GetVertexDataSize(), 1);
		}
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





	void VertexArray::SetAttribPointer
	(
		GLuint attribID, GLint elemCount,
		GLenum type, GLboolean normalized,
		GLuint size, GLsizei stride,
		GLuint localOffset, GLuint globalOffset,
		GLuint divisor
	)
	{
		if (elemCount > 4) {
			GLuint elemSize = (size / elemCount);
			GLuint part = 0;
			GLuint partSize = 0;
			for (elemCount; elemCount > 0; elemCount -=4)
			{
				partSize = part++ * elemSize;
				if (elemCount > 4)
					SetAttribPointer(attribID++, 4, type, normalized, size, stride, localOffset + partSize*4, globalOffset, divisor);
				else
					SetAttribPointer(attribID++, elemCount, type, normalized, size, stride, localOffset + partSize * elemCount, globalOffset, divisor);
			}
		}
		else {
			if (elemCount == 1) {
				if (type == GL_INT || type == GL_UNSIGNED_INT)
					GLCall(glVertexAttribIPointer(attribID, elemCount, type, stride, (GLvoid*)(localOffset + globalOffset)));
			}
			else
				GLCall(glVertexAttribPointer(attribID, elemCount, type, normalized, stride, (GLvoid*)(localOffset + globalOffset)));
			GLCall(glEnableVertexAttribArray(attribID));
			if (divisor)
				GLCall(glVertexAttribDivisor(attribID, divisor));
			//glm::vec4 v4;
			//glGetBufferSubData(GL_ARRAY_BUFFER, localOffset + globalOffset, 16, &v4);
			//OGLE_CORE_INFO("\nID: {0}\nOffset: {1}\nData: ({2}, {3}, {4}, {5})\n", attribID, localOffset + globalOffset, v4.x, v4.y, v4.z, v4.w);
		}
	}

	void VertexArray::SetAttribPointer(DataAttribute* attribute, GLsizei stride/*=0*/, GLuint localOffset /*= 0*/, GLuint globalOffset /*= 0*/, GLuint divisor /*= 0*/)
	{
		SetAttribPointer(attribute->AttribID, attribute->Count, attribute->Type, attribute->Normalized, attribute->Size, stride, localOffset, globalOffset, divisor);
	}

}