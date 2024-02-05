#pragma once
#include "OGLE/Buffer/Data/Data.h"

namespace OGLE{
	class Collection
	{
	public:
		const GLvoid* GetDataPtr();

		GLuint GetSize();

		GLuint GetLength();

		DataLayout& GetLayout();

		std::unordered_map<GLuint, DataAttribute*> GetAttributes();

	protected:
		Collection(const GLvoid* dataPtr, GLuint dataSize, GLuint dataLength, DataLayout layout, GLuint attributeIDTracker, GLuint bufferOffset = 0);

	private:
		const GLvoid* m_DataPtr;
		GLuint m_DataSize;
		GLuint m_DataLength;

		DataLayout m_DataLayout;

		std::unordered_map<GLuint, DataAttribute*> m_DataAttributes;
	};

	class VertexCollection : public Collection
	{
	public:
		VertexCollection(std::vector<Vertex>& vertices, DataLayout vertexLayout, GLuint attributeIDTracker);

	};

	class InstanceCollection : public Collection
	{
	public:
		InstanceCollection(std::vector<Instance>& instanceData, DataLayout instanceDataLayout, GLuint attributeIDTracker);
	};

	class VertexBufferData
	{
	public:
		VertexBufferData
		(
			std::vector<Vertex>& vertices,
			std::vector<Instance>* instanceData = nullptr,
			DataLayout vertexLayout= s_DefVertexDataLayout,
			DataLayout instanceDataLayout = s_DefInstanceDataLayout
		)
			: m_AttributeIDTracker(NewAttributeIDTracker()), m_VDC(vertices, vertexLayout, m_AttributeIDTracker)
		{
			if (instanceData) {
				m_IDC = new InstanceCollection(*instanceData, instanceDataLayout, m_AttributeIDTracker);
				m_IsInstanced = true;
			}
		}

		VertexCollection GetVDC() { return m_VDC; }
		InstanceCollection GetIDC() { return *m_IDC; }

		GLuint GetSize() { return m_VDC.GetSize() + ((m_IsInstanced) ? m_IDC->GetSize() : 0); }

		bool IsInstanced() { return m_IsInstanced; }
	private:
		GLuint m_AttributeIDTracker;

		VertexCollection m_VDC;
		InstanceCollection* m_IDC = nullptr;

		bool m_IsInstanced = false;
	};
}