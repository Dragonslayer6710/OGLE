#pragma once
#include "OGLE/Buffer/Buffer.h"

namespace OGLE {

	class VertexArray
	{
	public:

		static Scope<VertexArray> Create(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection);

		VertexArray(Ref<VertexCollection> vertexCollection, Ref<InstanceCollection> instanceCollection);

		~VertexArray();

		void Bind();
		void Unbind();

		Ref<VertexCollection> GetVertices();
		
		std::vector<GLushort>* GetIndices();
		GLuint GetElementCount();
		GLenum GetElementDataType();

		Ref<InstanceCollection> GetInstances();
		GLuint GetInstanceCount();
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
		Ref<VertexCollection> m_Vertices;

		Ref<VertexBuffer> m_IBO;
		Ref<InstanceCollection> m_Instances;

		bool m_IsBound = false;

	};

}