#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh
		(
			Shape& shape,
			InstanceList* instanceList = nullptr,
			DataLayout vertexLayout = s_DefVertexLayout,
			DataLayout instanceLayout = s_DefInstanceLayout
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{
			VertexCollection* vertices = shape.GetVertices();	

			InstanceCollection* instances;
			vertices->LinkCollection(m_AttributeIDTracker);

			if (instanceList) {
				instances = new InstanceCollection(*instanceList, instanceLayout);
				instances->LinkCollection(m_AttributeIDTracker);
			}
			m_VAO = new VertexArray(*vertices, *(shape.GetIndices()), instances);
		}
		
		VertexArray& GetVAO() { return *m_VAO; }

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
