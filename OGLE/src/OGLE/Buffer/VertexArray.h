#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:
		VertexArray(VertexCollection* vertices, std::vector<GLushort>* indices, InstanceDataCollection* instanceData = nullptr);

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

		void SetVBOAttribPointers();

	private:
		GLuint m_VertexArrayID;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;

		bool m_IsBound = false;
		bool m_RetainBind = false;
	};

}