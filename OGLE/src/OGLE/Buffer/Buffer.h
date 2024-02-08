#pragma once
#include "OGLE/Buffer/Data/Collection.h"

namespace OGLE{
	class Buffer
	{
	public:
		Buffer(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum bufferUsage);
		~Buffer();

		bool IsBound();
		void Bind();
		void Unbind();

	protected:	
		void SetData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

	protected:
		GLuint m_BufferID;
		GLenum m_BufferTarget;
		GLenum m_BufferUsage;

		bool m_IsBound = false;
	};
	template <typename T>
	
	class CollectionBuffer : public Buffer
	{
	public:
		CollectionBuffer(Collection<T>& collection, GLenum bufferUsage = GL_STATIC_DRAW) 
			: m_Collection(collection), Buffer(GL_ARRAY_BUFFER, collection.GetSize(), collection.GetData(), bufferUsage){}
		Collection<T> GetCollection() { return m_Collection; }
	protected:
		Collection<T> m_Collection;
	};

	class VertexBuffer : public CollectionBuffer<Vertex>
	{
	public:
		VertexBuffer(VertexCollection& vertexCollection, GLenum bufferUsage = GL_STATIC_DRAW)
			: CollectionBuffer(vertexCollection, bufferUsage) {}
	};

	class InstanceBuffer : public CollectionBuffer<Instance>
	{
	public:
		InstanceBuffer(InstanceCollection& instanceCollection, GLenum bufferUsage = GL_STATIC_DRAW)
			: CollectionBuffer(instanceCollection, bufferUsage) {}
	};


	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(std::vector<GLushort>& indices, GLenum bufferTarget = GL_STATIC_DRAW, GLenum elementDataType = GL_UNSIGNED_SHORT);

		GLuint GetElementCount() const;
		GLenum GetElementDataType() const;

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};
}