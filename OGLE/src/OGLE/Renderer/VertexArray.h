#pragma once
#include "OGLE/Renderer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:

		VertexArray()
		{
			GLCall(glGenVertexArrays(1, &m_ID));
		}

		~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_ID)); }

		void Bind() { GLCall(glBindVertexArray(m_ID)); }
		void Unbind() { GLCall(glBindVertexArray(0)); }

		VertexBuffer* GetVertexBuffer();
		void SetVertexBuffer(VertexBuffer& vbo);

		void SetAttribPointers();

		ElementBuffer* GetElementBuffer() { return m_EBO; };
		void SetElementBuffer(ElementBuffer& vbo);;

	private:
		GLuint m_ID;
		GLuint m_VertexCount;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;
	};

}