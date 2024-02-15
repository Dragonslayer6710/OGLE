#include "oglepch.h"
#include "OGLE/Buffer/VertexArray.h"

namespace OGLE {


	Scope<VertexArray> VertexArray::Create(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection)
	{
		return CreateScope<VertexArray>(vertexCollection, instanceCollection);
	}

	VertexArray::VertexArray(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection)
		: m_Vertices(vertexCollection), m_Instances(instanceCollection)
	{
		// Gen and Bind Vertex Array
		GLCall(glGenVertexArrays(1, &m_VertexArrayID));
		Bind();

		// Gen and Bind VBO
		m_VBO = VertexBuffer::Create(m_Vertices->GetSize(), m_Vertices->GetData(), m_Instances->GetUsage());
		m_VBO->Bind();

		// Init VBO attrib arrays then unbind vbo
		SetAttribPointers<VertexCollection>(m_Vertices);
		m_VBO->Unbind();

		// If instance data given
		if (m_Instances)
		{
			// Init and bind IBO
			m_IBO = VertexBuffer::Create(m_Instances->GetSize(), m_Instances->GetData(), m_Instances->GetUsage());
			m_IBO->Bind();

			// Init IBO Attrib Arrays then unbind IBO
			SetAttribPointers(m_Instances, 1);
			m_IBO->Unbind();
		}

		// Generate Element buffer then unbind VAO to close off VAO initialization
		m_EBO = ElementBuffer::Create(vertexCollection->GetIndices());
		Unbind();
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_VertexArrayID));
	}

	void VertexArray::Bind()
	{
		if (m_IsBound)
			return;
		GLCall(glBindVertexArray(m_VertexArrayID));
		m_IsBound = true;
		if (m_EBO)
			m_EBO->Bind();
	}

	void VertexArray::Unbind()
	{
		if (!m_IsBound)
			return;		
		GLCall(glBindVertexArray(0)); 
		m_IsBound = false; 
		if (m_EBO)
			m_EBO->Unbind();
	}

	Ref<VertexCollection> VertexArray::GetVertices()
	{
		return m_Vertices;
	}

	Ref<InstanceCollection> VertexArray::GetInstances()
	{
		return m_Instances;
	}

	bool VertexArray::CheckInstanced()
	{
		return m_IBO != nullptr;
	}


	void VertexArray::SetAttribPointer
	(
		GLuint attribID, GLint elemCount,
		GLenum type, GLboolean normalized,
		GLuint size, GLsizei stride,
		GLuint offset, GLuint divisor /*= 0*/, 
		GLuint subOffset /*= 0*/, GLuint subAttribID /*= 0*/
	)
	{
		if (elemCount > 4) {
			// Calc size of individual element then mult by 4 to get a sub attrib size
			GLuint elemSize = size / elemCount;
			GLuint subAttribSize = elemSize * 4;

			// Use the above assignments to enable a sub attrib pointer for part of the overall attribute
			SetAttribPointer(attribID, 4, type, normalized, subAttribSize, stride, offset,  divisor, subOffset, subAttribID);
			
			// remove amount of elements which have now been assigned to a 4-size pointer
			elemCount -= 4;

			// Recalculate total size of remaining elements
			size = elemSize * elemCount;

			// Recurse until all elements have been applied to pointers
			SetAttribPointer(attribID + 1, elemCount, type, normalized, size, stride, offset,  divisor, subOffset + subAttribSize, subAttribID + 1);
		}
		else {
			GLuint totalOffset = offset + subOffset;
			GLvoid* ptr = (GLvoid*)totalOffset;
			if (elemCount == 1) {
				if (type == GL_INT || type == GL_UNSIGNED_INT)
					GLCall(glVertexAttribIPointer(attribID, elemCount, type, stride, ptr));
			}
			else
				GLCall(glVertexAttribPointer(attribID, elemCount, type, normalized, stride, ptr));
			GLCall(glEnableVertexAttribArray(attribID));
			if (divisor)
				GLCall(glVertexAttribDivisor(attribID, divisor));
			glm::vec4 v4;
			glGetBufferSubData(GL_ARRAY_BUFFER, totalOffset, size, &v4);
			//OGLE_CORE_INFO("\nAttribute ID {0}:\n\tAttribute Size: {1}\t|\tOffset: {2}\t|\tElements: {3}\t|\tType: {4}\t|\tNormalized: {5}\nData: {6}\t|\tDivisor: {7}\n", attribID, size, totalOffset, elemCount, type, normalized, v4, divisor);
		}
	}

	void VertexArray::SetAttribPointer(DataAttribute* attribute, GLsizei stride/*=0*/, GLuint offset /*= 0*/, GLuint divisor /*=1/*/)
	{
		SetAttribPointer(attribute->AttribID, attribute->Count, attribute->Type, attribute->Normalized, attribute->Size, stride, offset, divisor);
	}

}