#pragma once
#include "OGLE/Buffer/Data/Collection.h"

namespace OGLE{
	class Buffer
	{
	public:
		Buffer(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum bufferUsage, bool nullInit = false);
		~Buffer();

		bool IsBound();
		void Bind();
		void Unbind();

	protected:	
		friend class VertexArray;
		void SetData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

	protected:
		GLuint m_BufferID;
		GLenum m_BufferTarget;
		GLenum m_BufferUsage;

		bool m_IsBound = false;
	};

	class VertexBuffer : public Buffer
	{
	public:
		static Ref<VertexBuffer> Create(GLsizeiptr size, const GLvoid* data, GLenum bufferUsage = GL_STATIC_DRAW, bool nullInit = false);

		VertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum bufferUsage, bool nullInit = false)
			: Buffer(GL_ARRAY_BUFFER, size, data, bufferUsage, nullInit) {}

	};

	class ElementBuffer : public Buffer
	{
	public:
		static Ref<ElementBuffer> Create(std::vector<GLushort>* indices, GLenum bufferTarget = GL_STATIC_DRAW, GLenum elementDataType = GL_UNSIGNED_SHORT);


		ElementBuffer(std::vector<GLushort>* indices, GLenum bufferTarget = GL_STATIC_DRAW, GLenum elementDataType = GL_UNSIGNED_SHORT);

	};
}