#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh
		(
			VertexCollection* m_Vertices,
			InstanceCollection* m_Instances = nullptr
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{			
			m_Vertices->LinkCollection(m_AttributeIDTracker);
			if (m_Instances != nullptr) {
				m_Instances->LinkCollection(m_AttributeIDTracker);
			}
			m_VAO = new VertexArray(*m_Vertices, m_Instances);
		}
		
		VertexArray& GetVAO() { return *m_VAO; }

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
