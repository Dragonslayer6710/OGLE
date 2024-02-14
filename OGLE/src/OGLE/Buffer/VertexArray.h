#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:
		VertexArray(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection);

		~VertexArray();

		void Bind();
		void Unbind();

		VertexBuffer& GetVertexBuffer();

		ElementBuffer& GetElementBuffer();
		GLuint GetElementCount();
		GLenum GetElementDataType();

		InstanceBuffer& GetInstanceBuffer();
		GLuint GetInstanceCount();
		bool CheckInstanced();

		void SetInstanceBuffer(Ref<InstanceCollection> instanceCollection);

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
		
		template<typename T>
		static void SetAttribPointers(Ref<Collection<T>> collection, GLuint divisor=0) {
			GLuint stride = collection->GetStride();
			for (auto& offsetAttrib : collection->GetAttributes())
				SetAttribPointer(offsetAttrib.second, stride, offsetAttrib.first, divisor);
		}

	private:
		GLuint m_VertexArrayID;

		Scope<VertexBuffer> m_VBO;
		Scope<InstanceBuffer> m_IBO;

		GLuint m_Instances = 1;
		bool m_IsInstanced = false;

		ElementBuffer* m_EBO = nullptr;

		bool m_IsBound = false;

	};

}