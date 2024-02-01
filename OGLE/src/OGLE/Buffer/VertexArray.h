#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:
		VertexArray(VertexBuffer& vbo, ElementBuffer& ebo);

		~VertexArray();

		void PrintStatus(const char* status);
		void PrintInitialized();
		void PrintBindStatus();

		void Bind();
		void Unbind();

		VertexBuffer* GetVertexBuffer();

		ElementBuffer* GetElementBuffer();;
		GLuint GetElementCount();
		GLenum GetElementDataType();

		GLuint GetInstanceCount();;

	private:
		void InitVertexArray(VertexBuffer& vbo, ElementBuffer& ebo);

		void LinkNewVertexBufferToVertexArray(VertexBuffer& vbo);
		void SetVertexBuffer(VertexBuffer& vbo);
		void LinkVertexBufferToVertexArray();
		void BindVertexBuffer();
		void UnbindVertexBuffer();

		void SetVBOAttribPointers();

		void LinkNewElementBufferToVertexArray(ElementBuffer& ebo);
		void SetElementBuffer(ElementBuffer& ebo);
		void LinkElementBufferToVertexArray();
		void BindElementBuffer();
		void UnbindElementBuffer();

	private:
		GLuint m_VertexArrayID;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;

		GLuint m_InstanceCount;

		bool m_IsBound = false;
		bool m_RetainBind = false;
	};

}