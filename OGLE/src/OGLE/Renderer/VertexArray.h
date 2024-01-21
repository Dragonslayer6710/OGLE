#pragma once
#include "OGLE/Renderer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:
		VertexArray(VertexBuffer& vbo, ElementBuffer& ebo)
			
		{
			InitVertexArray(vbo, ebo);
		}

		~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_VertexArrayID)); }

		void PrintStatus(const char* status) { std::cout << "Vertex Array (ID " << m_VertexArrayID << "): " << status << std::endl; }
		void PrintInitialized() { PrintStatus("Initialized"); }
		void PrintBindStatus() { PrintStatus((m_IsBound) ? "Bound" : "Unbound"); }

		void Bind();
		void Unbind();

		VertexBuffer* GetVertexBuffer()	{ return m_VBO; }

		ElementBuffer* GetElementBuffer() { return m_EBO; };
		GLuint GetElementCount() { return m_EBO->GetElementCount(); }
		GLenum GetElementDataType() { return m_EBO->GetElementDataType(); }

	private:
		void InitVertexArray(VertexBuffer& vbo, ElementBuffer& ebo) {
			GLCall(glGenVertexArrays(1, &m_VertexArrayID));
			//PrintInitialized();

			m_RetainBind = true;
			Bind();
			LinkNewVertexBufferToVertexArray(vbo);
			LinkNewElementBufferToElementArray(ebo);
			Unbind();
			m_RetainBind = false;
		}

		void LinkNewVertexBufferToVertexArray(VertexBuffer& vbo)
		{
			SetVertexBuffer(vbo); LinkVertexBufferToVertexArray();
		}
		void SetVertexBuffer(VertexBuffer& vbo) { m_VBO = &vbo; }
		void LinkVertexBufferToVertexArray();
		void BindVertexBuffer() {
			m_VBO->Bind();
		}
		void UnbindVertexBuffer() {
			m_VBO->Unbind();
		}
		void SetVBOAttribPointers();

		void LinkNewElementBufferToElementArray(ElementBuffer& ebo)
		{
			SetElementBuffer(ebo); LinkElementBufferToVertexArray();
		}
		void SetElementBuffer(ElementBuffer& ebo) { m_EBO = &ebo; }
		void LinkElementBufferToVertexArray();
		void BindElementBuffer() {
			m_EBO->Bind();
		}
		void UnbindElementBuffer() {
			m_EBO->Unbind();
		}

	private:
		GLuint m_VertexArrayID;
		GLuint m_VertexCount;

		VertexBuffer* m_VBO;
		ElementBuffer* m_EBO;

		bool m_IsBound = false;
		bool m_RetainBind = false;
	};

}