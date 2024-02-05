#pragma once
#include "OGLE/Buffer/Data/Collection.h"

namespace OGLE{
	class Buffer
	{
	public:
		Buffer(GLenum target, GLsizeiptr size=0, const GLvoid* data=NULL, GLenum bufferUsage = GL_STATIC_DRAW );
		~Buffer();

		void Bind();
		void Unbind();

		GLuint GetSize();

	protected:
		void SetData(GLintptr offset = 0, GLsizeiptr size = 0, const GLvoid* data = NULL);
		void BufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
		virtual void InitBuffer();

	private:
		void BufferData(GLsizeiptr size, const GLvoid* data, GLenum bufferUsage);

	protected:
		GLsizeiptr m_Size;
		const GLvoid* m_DataPtr;

	private:
		GLuint m_BufferID;
		GLenum m_BufferTarget;
		GLenum m_BufferUsage;

	};



	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(VertexBufferData& vertexBufferData, GLenum bufferUsage = GL_STATIC_DRAW);

		bool IsInstanced();
		GLuint GetInstanceCount();

		std::unordered_map<GLuint, DataAttribute*> GetVertexAttributes();

		GLuint GetVertexDataSize();
		GLuint GetInstanceDataSize();

		std::unordered_map<GLuint, DataAttribute*> GetInstanceDataAttributes();
	private:
		bool m_IsInstanced;		
		
		VertexBufferData m_VertexBufferData;
	};




	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(std::vector<GLushort>* indices, GLenum bufferTarget = GL_STATIC_DRAW, GLenum elementDataType = GL_UNSIGNED_SHORT);

		GLuint GetElementCount() const;
		GLenum GetElementDataType() const;

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};
}