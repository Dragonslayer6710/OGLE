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

		ElementBuffer* GetElementBuffer();;
		GLuint GetElementCount();
		GLenum GetElementDataType();

		GLuint GetInstanceCount();;

	private:

		void SetVertexDataPointers();
		void SetInstanceDataPointers();

	private:
		GLuint m_VertexArrayID;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;

		bool m_IsBound = false;

		GLuint m_NextAttributeIndex = 0;
	};

}