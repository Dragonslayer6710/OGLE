#pragma once
#include "OGLE/Geometry/Vertex/Vertex.h"

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
		Buffer(const Buffer& other); // Copy Constructor


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
		void ExtendBuffer(GLsizeiptr additionalSize);

	protected:
		GLuint m_BufferID;
		GLsizeiptr m_Size;
		bool m_Resizable = false;

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
		class InstanceBuffer : public Buffer
		{
		public:
			InstanceBuffer(const VertexBuffer& vbo, std::vector<glm::mat4>& instanceMatrices);
			GLuint GetInstanceCount() { return m_InstanceCount; }
		private:
			GLuint m_InstanceCount;
		};

	public:
		VertexBuffer(std::vector<Vertex>& vertices, VertexLayout layout = DefVertLayout);
		VertexBuffer(std::vector<Vertex>& vertices, std::vector<glm::mat4>& instanceMatrices, VertexLayout layout = DefVertLayout);
		VertexBuffer(const VertexBuffer& other);

		void BindInstanceBuffer() { if (m_IBO) m_IBO->Bind(); }
		void UnbindInstanceBuffer() { if (m_IBO) m_IBO->Unbind(); }	

		GLuint GetStride() const { return m_Stride; }
		GLuint GetAttribCount() const { return m_AttribCount; }

		std::unordered_map<GLuint, VertexAttribute*> GetVertexAttributes() { return m_VertexAttributes; }
		//std::unordered_map<GLuint, MatrixAttribute*> GetMatrixAttributes() { return m_MatrixAttributes; }

		InstanceBuffer& GetInstanceBuffer() { return *m_IBO; }
		void SetInstanceBuffer(std::vector<glm::mat4> instanceMatrices);

		GLuint GetInstanceCount() { return m_InstanceCount; }
		bool CheckInstanced() { return m_IsInstanced; }
	protected:
		void SetIntanceCount();

		void AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized = GL_FALSE);
	private:
		void InitVertexBuffer(VertexLayout layout);
	protected:
		GLuint m_InstanceCount;
		bool m_IsInstanced;
		InstanceBuffer* m_IBO;
	private:
		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;

		std::unordered_map<GLuint, VertexAttribute*> m_VertexAttributes = std::unordered_map<GLuint, VertexAttribute*>();
		//std::unordered_map<GLuint, MatrixAttribute*> m_MatrixAttributes = std::unordered_map<GLuint, MatrixAttribute*>();
	};

	// Buffer to hold the order in which to use the vertices in the vertexbuffer
	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType = GL_UNSIGNED_SHORT);
		ElementBuffer(const ElementBuffer& other);

		GLuint GetElementCount() const { return m_ElementCount; }
		GLenum GetElementDataType() const { return m_ElementDataType; }

	protected:

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};

	

}