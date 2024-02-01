#pragma once
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {
	class Drawable {
	public:
		Drawable(Mesh* mesh): m_Mesh(mesh){}
		Mesh& GetMesh() { return *m_Mesh; }
	private:
		Mesh* m_Mesh;
	};
}
