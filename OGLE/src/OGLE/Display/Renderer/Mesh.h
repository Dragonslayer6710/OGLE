#pragma once

#include "OGLE/Maths/Geometry/Shape.h"

namespace OGLE {

	class Mesh 
	{
	public:
		static Scope<Mesh> Create(Ref<Shape> shape)
		{
			return CreateScope<Mesh>(shape);
		}


		Mesh(Ref<Shape> shape)
			: m_Vertices(shape->GetVertices()), m_Instances(shape->GetInstances())
		{
		}

		Ref<VertexCollection> GetVertices() { return m_Vertices; }
		Ref<InstanceCollection> GetInstances() { return m_Instances; }

	protected:
		Mesh() {
		}

		Ref<VertexCollection> m_Vertices;
		Ref<InstanceCollection> m_Instances;

	private:		


	};
}
