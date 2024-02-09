#pragma once
#include "OGLE/Buffer/Data/Data.h"

namespace OGLE{
	template <typename T>
	class Collection
	{
	public:
		Collection(DataList<T>& dataList, DataLayout& dataLayout)
			: m_DataList(dataList), m_DataLayout(dataLayout), m_Data(m_DataList.GetData()), m_Length(m_DataList.GetLength()), m_Size(m_DataList.GetSize())
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
		DataList<T> GetDataList() { return m_DataList; }

		const GLvoid* GetData() { return m_Data; }
		GLuint GetLength() { return m_Length; }
		GLuint GetSize() { return m_Size; }
		GLuint GetStride() { return m_Stride; }


	private:
		std::unordered_map<GLuint, DataAttribute*> m_DataAttributes;
		DataList<T> m_DataList;
		DataLayout m_DataLayout;

		const GLvoid* m_Data;
		GLuint m_Length;
		GLuint m_Size;
		GLuint m_Stride = 0;
	};

	class VertexCollection : public Collection<Vertex>
	{
	public:
		VertexCollection(VertexList& vertexList, DataLayout vertexLayout)
			: Collection(vertexList, vertexLayout) {}
	};

	class InstanceCollection : public Collection<Instance>
	{
	public:
		InstanceCollection(InstanceList& instanceList, DataLayout instanceLayout)
			: Collection(instanceList, instanceLayout) {}
	};
}