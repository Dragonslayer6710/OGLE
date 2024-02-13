#pragma once

#include "OGLE/Maths/Geometry/Shape.h"

namespace OGLE {

	class Mesh 
	{
	public:
		static Mesh* Create(Shape* shape)
		{

			if (shape->CheckInstanced())
				return new Mesh(shape->GetVertices(), shape->GetInstances());
			else
				return new Mesh(shape->GetVertices(), nullptr);
		}

		VertexArray* GetVAO() { return m_VAO; }

	protected:
		Mesh
		(
			VertexCollection* vertices,
			InstanceCollection* instances = nullptr
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{			
			vertices->LinkCollection(m_AttributeIDTracker);
			if (instances != nullptr) {
				instances->LinkCollection(m_AttributeIDTracker);
			}
			m_VAO = new VertexArray(vertices, instances);
		}

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
