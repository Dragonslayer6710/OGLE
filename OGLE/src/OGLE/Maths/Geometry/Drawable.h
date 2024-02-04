#pragma once
#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {
	class Drawable {
	public:
		Drawable(Mesh* mesh, Texture* texture)
			: m_Mesh(mesh), m_Texture(texture){}
		Mesh& GetMesh() { return *m_Mesh; }
		Texture& GetTexture() { return *m_Texture; }
	private:
		Mesh* m_Mesh;
		Texture* m_Texture;
	};
}
