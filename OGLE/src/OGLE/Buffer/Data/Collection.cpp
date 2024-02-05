#include "oglepch.h"
#include "OGLE/Buffer/Data/Collection.h"

namespace OGLE {

	const GLvoid* Collection::GetDataPtr()
	{
		return m_DataPtr;
	}

	GLuint Collection::GetSize()
	{
		return m_DataSize;
	}

	GLuint Collection::GetLength()
	{
		return m_DataLength;
	}

	OGLE::DataLayout& Collection::GetLayout()
	{
		return m_DataLayout;
	}

	std::unordered_map<GLuint, DataAttribute*> Collection::GetAttributes()
	{
		return m_DataAttributes;
	}

	Collection::Collection(const GLvoid* dataPtr, GLuint dataSize, GLuint dataLength, DataLayout layout, GLuint attributeIDTracker, GLuint bufferOffset /*= 0*/) 
		: m_DataPtr(dataPtr), m_DataSize(dataSize), m_DataLength(dataLength), m_DataLayout(layout)
	{
		for (DataAttributeInfo attribData : GetLayout().AttributeData) {
			m_DataAttributes[bufferOffset] = GetNewDataAttribute(attributeIDTracker, attribData.m_ControlType, attribData.Normalized);
			bufferOffset += m_DataAttributes[bufferOffset]->Size;
		}
	}

	VertexCollection::VertexCollection(std::vector<Vertex>& vertices, DataLayout vertexLayout, GLuint attributeIDTracker) 
		: Collection(vertices.data(), vertices.size() * sizeof(Vertex), vertices.size(), vertexLayout, attributeIDTracker)
	{

	}


	InstanceCollection::InstanceCollection(std::vector<Instance>& instanceData, DataLayout instanceDataLayout, GLuint attributeIDTracker) 
		: Collection
		(
			instanceData.data(),
			instanceData.size() * sizeof(Instance),
			instanceData.size(),
			instanceDataLayout, 
			attributeIDTracker
		)
	{

	}

}