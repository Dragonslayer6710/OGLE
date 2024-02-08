#pragma once
#include "OGLE/Buffer/VertexArray.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh
		(
			VertexList& vertexList,
			std::vector<GLushort>& indices,
			InstanceList* instanceList = nullptr,
			DataLayout vertexLayout = s_DefVertexLayout,
			DataLayout instanceLayout = s_DefInstanceLayout
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{
			VertexCollection* vertexCollection = new VertexCollection(vertexList, vertexLayout, m_AttributeIDTracker);
			InstanceCollection* instanceCollection;
			if (instanceList)
				instanceCollection = new InstanceCollection(*instanceList, instanceLayout, m_AttributeIDTracker);
			m_VAO = new VertexArray(*vertexCollection, indices, instanceCollection);
		}
			

		Mesh(VertexCollection& vertexCollection, std::vector<GLushort>& indices, InstanceCollection* instanceCollection = nullptr)
			: m_AttributeIDTracker(NewAttributeIDTracker()) 
		{
			m_VAO = new VertexArray(vertexCollection, indices, instanceCollection);
		}
		VertexArray& GetVAO() { return *m_VAO; }

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
