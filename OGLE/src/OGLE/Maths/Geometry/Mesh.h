#pragma once

#include "OGLE/Maths/Geometry/Shape.h"

namespace OGLE {

	class Mesh 
	{
	public:
		static Ref<Mesh> Create(Ref<Shape> shape)
		{

			if (shape->CheckInstanced())
				return CreateScope<Mesh>(shape->GetVertices(), shape->GetInstances());
			else
				return CreateScope<Mesh>(shape->GetVertices(), nullptr);
		}

		VertexArray* GetVAO() { return m_VAO; }

		Mesh
		(
			Ref<VertexCollection> vertices,
			Ref<InstanceCollection> instances = nullptr
		) 
			: m_AttributeIDTracker(NewAttributeIDTracker())
		{			
			vertices->LinkCollection(m_AttributeIDTracker);
			if (instances != nullptr) {
				instances->LinkCollection(m_AttributeIDTracker);
			}
			m_VAO = new VertexArray(vertices, instances);
		}

		~Mesh()
		{
			DeleteAttributeIDTracker(m_AttributeIDTracker);
		}

	private:
		GLuint m_AttributeIDTracker;
		VertexArray* m_VAO;
	};
}
