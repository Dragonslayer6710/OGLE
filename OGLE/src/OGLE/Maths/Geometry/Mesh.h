#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
#include "OGLE/Display/Renderer/Texture.h"

namespace OGLE {
	class Mesh 
	{
	public:
		Mesh
		(
			VertexCollection* Vertices,
			InstanceCollection* Instances = nullptr
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{			
			Vertices->LinkCollection(m_AttributeIDTracker);
			if (Instances != nullptr) {
				Instances->LinkCollection(m_AttributeIDTracker);
			}
			m_VAO = new VertexArray(*Vertices, Instances);
		}
		
		VertexArray& GetVAO() { return *m_VAO; }

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
