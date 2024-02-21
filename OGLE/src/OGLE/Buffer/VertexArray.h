#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:

		static Scope<VertexArray> Create(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection, bool nullInstInit = false);

		VertexArray(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection, bool nullInstInit = false);

		~VertexArray();

		void Bind();
		void Unbind();

		void SetInstanceData(GLuint offset, GLuint size, const GLvoid* data);

		Ref<VertexBuffer> GetVertexBuffer();
		Ref<VertexBuffer> GetInstanceBuffer();
		Ref<ElementBuffer> GetElementBuffer();

		bool CheckInstanced();

	private:
		static void SetAttribPointer
		(
			GLuint attribID, GLint elemCount,
			GLenum type, GLboolean normalized,
			GLuint size, GLsizei stride, 
			GLuint offset, GLuint divisor, 
			GLuint subOffset = 0, GLuint subAttribID=0
		);

		static void SetAttribPointer
		(
			DataAttribute* attribute,
			GLsizei stride = 0, 
			GLuint offset = 0,
			GLuint divisor = 0
		);
		
		template<typename T2>
		static void SetAttribPointers(Ref<T2> collection, GLuint divisor=0) {
			GLuint stride = collection->GetStride();
			for (auto& offsetAttrib : collection->GetAttributes())
				SetAttribPointer(offsetAttrib.second, stride, offsetAttrib.first, divisor);
		}

	private:
		GLuint m_VertexArrayID;

		Ref<VertexBuffer> m_VBO;
		Ref<ElementBuffer> m_EBO;
		Ref<VertexBuffer> m_IBO;

		bool m_IsBound = false;

	};

}