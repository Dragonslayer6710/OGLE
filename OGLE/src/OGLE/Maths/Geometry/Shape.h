#pragma once

#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {
	class Shape
	{
	public:
		Shape(VertexList vertexList, std::vector<GLushort> indices, InstanceList* instanceList)
			: m_Mesh(new Mesh(vertexList, indices, instanceList))
		{}
/*

		Shape(VertexList vertexList, std::vector<GLushort> indices, InstanceList* instanceList)
			: m_Mesh(new Mesh(vertexList, indices, instanceList))
		{}*/

		Mesh& GetMesh() { return *m_Mesh; }
	private:
		Mesh* m_Mesh;
	};
}