#pragma once
#include "OGLE/Buffer/Data/Data.h"

namespace OGLE{
	class OldBuffer
	{
	public:
		OldBuffer(GLenum bufferTarget, GLsizeiptr size, const GLvoid* data, const char* prefix = "", GLenum bufferUsage = GL_STATIC_DRAW);
		OldBuffer(const OldBuffer& other); // Copy Constructor


		// Buffer referenced by m_ID no longer needed, so deleted
		~OldBuffer();

		void PrintStatus(const char* status);
		void PrintInitialized();
		void PrintBindStatus();

		// Buffer referenced by m_ID is bound to the usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.)
		virtual void Bind();

		// Buffer usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.) is unbound from any pointer
		virtual void Unbind();

		GLsizeiptr GetSize() const;
		
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

	class OldVertexBuffer : public OldBuffer
	{
	public:
		class InstanceBuffer : public OldBuffer
		{
		public:
			InstanceBuffer(std::vector<glm::mat4>& instanceMatrices);
			GLuint GetInstanceCount();
		private:
			GLuint m_InstanceCount;
		};

	public:
		OldVertexBuffer(VertexCollection& vertices);
		OldVertexBuffer(VertexCollection& vertices, std::vector<glm::mat4>& instanceMatrices);
		OldVertexBuffer(const OldVertexBuffer& other);

		void BindInstanceBuffer();
		void UnbindInstanceBuffer();	

		GLuint GetStride() const;
		GLuint GetAttribCount() const;

		std::unordered_map<GLuint, DataAttribute*> GetVertexAttributes();
		//std::unordered_map<GLuint, MatrixAttribute*> GetMatrixAttributes() { return m_MatrixAttributes; }

		InstanceBuffer& GetInstanceBuffer();

		GLuint GetInstanceCount();
		bool CheckInstanced();
	protected:
		void InitInstanceBuffer(std::vector<glm::mat4> instanceMatrices);

		void InitInstanceCount();

		void AddVertexAttribute(DataAttributeType attribType, GLboolean normalized = GL_FALSE);
	private:
		void InitVertexBuffer(DataLayout layout);
	protected:
		GLuint m_InstanceCount = 0;
		bool m_IsInstanced;
		InstanceBuffer* m_IBO = nullptr;
	private:
		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;

		std::unordered_map<GLuint, DataAttribute*> m_VertexAttributes = std::unordered_map<GLuint, DataAttribute*>();
	};

	class OldElementBuffer : public OldBuffer
	{
	public:
		OldElementBuffer(std::vector<GLushort>& indices, GLenum elementDataType = GL_UNSIGNED_SHORT);
		OldElementBuffer(const OldElementBuffer& other);

		GLuint GetElementCount() const;
		GLenum GetElementDataType() const;

	protected:

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};

	

}