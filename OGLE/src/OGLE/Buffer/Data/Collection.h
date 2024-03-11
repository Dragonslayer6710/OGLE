#pragma once
#include "OGLE/Buffer/Data/Data.h"

namespace OGLE{
	template <typename T>
	class Collection
	{
	public:

		Collection(ContVector<T>& data, DataLayout dataLayout, GLenum bufferUsage)
			: m_Elements(new ContVector<T>(data)), m_CompressedElements(new ContVector<T>(data)), m_DataLayout(dataLayout), m_BufferUsage(bufferUsage)
		{
		}

		void LinkCollection(GLuint attributeIDTracker)
		{
			for (const DataAttributeInfo& attribInfo : m_DataLayout.AttributeData)
			{
				m_DataAttributes[m_Stride] = GetNewDataAttribute(attributeIDTracker, attribInfo.Type, attribInfo.Normalized);
				m_Stride += m_DataAttributes[m_Stride]->Size;
			}
		}

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_DataAttributes; };
		
		DataLayout GetLayout() { return m_DataLayout; }

		ContVector<T>& GetElements() { return *m_Elements; }

		std::vector<Ref<Instance>>* GetSubset(size_t startIndex, size_t length, bool autoResize = false)
		{
			return m_Elements->GetSubset(startIndex, length, autoResize);
		}

		GLuint GetLength() { return m_Elements->size(); }
		GLuint GetSize() { return GetLength() * sizeof(T); }
		const GLvoid* GetData() {
			return m_Elements->data();
		}

		GLuint GetCompressedLength(bool forceUpdate = false) { return GetCompressedElements(forceUpdate)->size(); }
		GLuint GetCompressedSize(bool forceUpdate = false) { return GetCompressedLength(forceUpdate) * sizeof(T); }
		const GLvoid* GetCompressedData(bool forceUpdate = false) {
			return GetCompressedElements(forceUpdate)->data();
		}

		GLuint GetStride() { return m_Stride; }
		GLenum GetUsage() { return m_BufferUsage; }

		bool IsEmpty() { return !GetLength(); }	
		
		void ReserveInstances(GLuint size, GLuint compressedSize)
		{
			m_Elements->reserve(size);
			m_CompressedElements->reserve(compressedSize);
		}

		template<std::size_t N>
		void AddElements(const std::array<Instance, N>& elements)
		{
			return m_Elements->insert(elements);
		}

		void AddElements(std::vector<T>& elements)
		{
			m_Elements->insert(elements);
		}

		void AddElements(ContVector<T>& elements)
		{
			m_Elements->insert(elements);
		}

		void AddElement(T& element)
		{
			m_Elements->emplace_back(element);
		}

		void InsertElement(GLuint index, const T& elements) {
			if (index >= m_Elements->size()) {
				m_Elements->resize(index + 1);
			}
			(*m_Elements)[index] = elements;
		}

		void RemoveElement(GLuint index)
		{
			if (index >= m_Elements->size())
			{
				OGLE_CORE_ASSERT("Index out of bounds in RemoveElement()");
				return;
			}

			m_Elements->erase(index);
		}

		Ref<T> GetElement(GLuint index)
		{
			return m_Elements[index];
		}
	protected:
		ContVector<T>* GetCompressedElements(bool forceUpdate = false) {
			if (m_CompressedElements->size() == m_Elements->size())
				return m_Elements;
			if (!m_CompressedElements->empty())
				return m_CompressedElements;
			int culledFaces = 0;
			for (T& elem : *m_Elements) {
				// If the current element is non-zero
				if (!elem.IsNull()) {
					m_CompressedElements->emplace_back(elem);
				}
				else
					culledFaces++;
			}
			return m_CompressedElements;
		}

	private:		
		ContVector<T>* m_Elements;
		ContVector<T>* m_CompressedElements;

		std::unordered_map<GLuint, DataAttribute*> m_DataAttributes;
		DataLayout m_DataLayout;

		GLuint m_Stride = 0;
		GLenum m_BufferUsage;
	};

	class VertexCollection : public Collection<Vertex>
	{
	public:
		static Scope<VertexCollection> Create(ContVector<Vertex>& vertices, std::vector<GLushort>& indices) {
			return CreateScope<VertexCollection>(vertices, indices);
		}

		VertexCollection(ContVector<Vertex>& vertices, std::vector<GLushort>& indices, GLenum elementDataType = GL_UNSIGNED_SHORT)
			: Collection(vertices, s_VertexLayout, GL_STATIC_DRAW),
			m_Indices(new std::vector<GLushort>(indices)),
			m_ElementCount(indices.size()),
			m_ElementDataType(elementDataType) {}

		ContVector<Vertex>& GetVertices() { return GetElements(); }
		std::vector<GLushort>* GetIndices() { return m_Indices; }

		GLuint GetElementCount() const
		{
			return m_ElementCount;
		}

		GLenum GetElementDataType() const
		{
			return m_ElementDataType;
		}

	private:
		GLuint m_ElementCount;
		GLenum m_ElementDataType;

	private:
		std::vector<GLushort>* m_Indices;
	};

	class InstanceCollection : public Collection<Instance>
	{
	public:
		static Scope<InstanceCollection> Create(ContVector<Instance>& instances)
		{
			return CreateScope<InstanceCollection>(instances);
		}

		InstanceCollection(ContVector<Instance>& instances, GLenum bufferUsage = GL_DYNAMIC_DRAW)
			: Collection(instances, s_InstanceLayout, bufferUsage) {}

		ContVector<Instance>& GetInstances() { return GetElements(); }

		friend class Shape;
	};
}