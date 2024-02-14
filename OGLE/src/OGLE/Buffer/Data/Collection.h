#pragma once
#include "OGLE/Buffer/Data/Data.h"

namespace OGLE{
	template <typename T>
	class Collection
	{
	public:

		Collection(std::vector<T>& data, DataLayout dataLayout)
			: m_Elements(new std::vector(data)), m_DataLayout(dataLayout)
		{
		}

		void LinkCollection(GLuint attributeIDTracker)
		{
			for (DataAttributeInfo attribInfo : m_DataLayout.AttributeData)
			{
				m_DataAttributes[m_Stride] = GetNewDataAttribute(attributeIDTracker, attribInfo.Type, attribInfo.Normalized);
				m_Stride += m_DataAttributes[m_Stride]->Size;
			}
		}

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_DataAttributes; };

		GLuint GetLength() { return CompressElements()->size(); }
		GLuint GetSize() { return GetLength() * sizeof(T); }
		GLuint GetStride() { return m_Stride; }

		bool IsEmpty() { return !GetLength(); }

		std::vector<T>* GetElements() { return m_Elements; }
		const GLvoid* GetData() { 
			return CompressElements()->data(); }
	
	//protected:
		std::vector<T>* CompressElements() {
			if (m_Length == m_Elements->size())
				return m_Elements;
			std::vector<T>* retVector = new std::vector<T>(*m_Elements);
			int nonNullIndex = 0;
			for (int i = 0; i < retVector->size(); ++i) {
				// If the current element is non-zero
				if (!(*retVector)[i].IsNull()) {
					// Shift the non-zero element to the nonZeroIndex position
					(*retVector)[nonNullIndex] = (*retVector)[i];
					// Increment the nonZeroIndex
					++nonNullIndex;
				}
			}

			// Resize the vector to remove the trailing zeros
			retVector->resize(nonNullIndex);
			return retVector;
		}

		void AddElements(std::vector<T>& data)
		{
			m_Elements->insert(m_Elements->end(), data.begin(), data.end());
		}
		void AddElement(T& data)
		{
			m_Elements->push_back(data);
		}

		void InsertElement(GLuint index, T data) {
			if (index >= GetElements()->size())
				m_Elements->resize(index + 1, T());
			(*m_Elements)[index] = data;
		}

		void RemoveElement(GLuint index)
		{
			(*m_Elements)[index] = T();
		}

		T GetElement(GLuint index)
		{
			return (*m_Elements)[index];
		}

	private:		
		std::vector<T>* m_Elements;	

		std::unordered_map<GLuint, DataAttribute*> m_DataAttributes;
		DataLayout m_DataLayout;

		GLuint m_Length;
		GLuint m_Size;
		GLuint m_Stride = 0;
	};

	class VertexCollection : public Collection<Vertex>
	{
	public:
		static Ref<VertexCollection> Create(std::initializer_list<Vertex>& data, std::vector<GLushort>& indices)
		{
			return CreateRef <VertexCollection>(data, indices);
		}

		VertexCollection(std::initializer_list<Vertex>& data, std::vector<GLushort>& indices)
			: VertexCollection(std::vector(data), indices) {}

		std::vector<Vertex>* GetVertices() { return GetElements(); }
		std::vector<GLushort>* GetIndices() { return m_Indices; }

	private:
		VertexCollection(std::vector<Vertex>& vertices, std::vector<GLushort>& indices)
			: Collection(vertices, s_VertexLayout), m_Indices(new std::vector<GLushort>(indices)) {}

	private:
		std::vector<GLushort>* m_Indices;
	};

	class InstanceCollection : public Collection<Instance>
	{
	public:
		static Ref<InstanceCollection> Create(std::initializer_list<Instance>* data = nullptr)
		{
			return CreateRef <InstanceCollection>(data);
		}

		InstanceCollection(std::initializer_list<Instance>* data = nullptr)
			: InstanceCollection((data != nullptr) ? std::vector(*data) 
				: std::vector<Instance>()) {}

		std::vector<Instance>* GetInstances() { return GetElements(); }		
		
		friend class Shape;
	private:
		InstanceCollection(std::vector<Instance>& instances)
			: Collection(instances, s_InstanceLayout) {}

	};
}