#pragma once
#include "OGLE/Renderer/Vertex/Vertex.h"

namespace OGLE{
	class Buffer
	{
	public:
		Buffer(GLenum bufferTarget, GLsizeiptr size, const GLvoid* data, const char* prefix = "", GLenum bufferUsage = GL_STATIC_DRAW)
			: m_BufferTarget(bufferTarget), m_Size(size), m_Data(data), m_BufferUsage(bufferUsage), m_Prefix(prefix)
		{
			InitBuffer();
			AllocateBuffer();
		}

		// Buffer referenced by m_ID no longer needed, so deleted
		~Buffer() { GLCall(glDeleteBuffers(1, &m_BufferID)); }

		void PrintStatus(const char* status) { std::cout << m_Prefix << "Buffer (ID " << m_BufferID << "): " << status << std::endl; }
		void PrintInitialized() { PrintStatus("Initialized"); }
		void PrintBindStatus() { PrintStatus((m_IsBound) ? "Bound" : "Unbound"); }

		// Buffer referenced by m_ID is bound to the usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.)
		virtual void Bind();

		// Buffer usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.) is unbound from any pointer
		virtual void Unbind();

		GLsizeiptr GetSize() const { return m_Size; }
		
		virtual void UpdateData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

		virtual void ResetData(GLsizeiptr size, const GLvoid* data);

	protected:
		// Add Data to Buffer
		void SetData(GLsizeiptr size, const GLvoid* data);
		void InitBuffer();
	private:
		// Generate a buffer referenced by m_ID
		void AllocateBuffer();
		void BufferData() const;
		void BufferSubData(GLintptr offset=0, GLsizeiptr size=0, const GLvoid* data=NULL);

	protected:
		GLuint m_BufferID;
		GLsizeiptr m_Size;
		const GLvoid* m_Data;

		const char* m_Prefix;

	private:
		GLenum m_BufferTarget;
		GLenum m_BufferUsage;

		bool m_IsBound = false;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(std::vector<Vertex>& vertices, VertexLayout layout = DefVertLayout);

		GLuint GetStride() const { return m_Stride; }
		GLuint GetAttribCount() const { return m_AttribCount; }

		std::unordered_map<GLuint, VertexAttribute*> GetAttributes() { return m_VertexAttributes; }

	protected:
		void AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized = GL_FALSE);

	private:
		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;

		std::unordered_map<GLuint, VertexAttribute*> m_VertexAttributes = std::unordered_map<GLuint, VertexAttribute*>();
	};

	// Buffer to hold the order in which to use the vertices in the vertexbuffer
	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType = GL_UNSIGNED_SHORT);
		
		GLuint GetElementCount() const { return m_ElementCount; }
		GLenum GetElementDataType() const { return m_ElementDataType; }

	protected:

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};

	class InstanceBuffer : public Buffer
	{
	public:
		InstanceBuffer(VertexBuffer& vbo, std::vector<float> offsets) : Buffer(GL_ARRAY_BUFFER, sizeof(float)* offsets.size(), offsets.data(), "Instance ", GL_STATIC_DRAW)
		{
			GLuint index = vbo.GetAttribCount();
			Bind();
			glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(index);
			glVertexAttribDivisor(index, 1);
			Unbind();
		}
	};
}