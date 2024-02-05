#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:
		VertexArray(VertexBufferData& vertexBufferData, std::vector<GLushort>& indices);

		~VertexArray();

		void PrintStatus(const char* status);
		void PrintInitialized();
		void PrintBindStatus();

		void Bind();
		void Unbind();

		VertexBuffer* GetVertexBuffer();

		ElementBuffer* GetElementBuffer();
		GLuint GetElementCount();
		GLenum GetElementDataType();

		GLuint GetInstanceCount();

	private:
		void VertexArray::SetAttribPointer
		(
			GLuint attribID, GLint elemCount,
			GLenum type, GLboolean normalized,
			GLuint size, GLsizei stride, 
			GLuint localOffset,	GLuint globalOffset,
			GLuint divisor
		);

		void SetAttribPointer
		(
			DataAttribute* attribute,
			GLsizei stride = 0, 
			GLuint localOffset = 0,
			GLuint globalOffset = 0,
			GLuint divisor = 0			
		);

	private:
		GLuint m_VertexArrayID;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;

		bool m_IsBound = false;

		GLuint m_NextAttributeIndex = 0;
	};

}