#pragma once

#include "OGLE/Maths/Geometry/Drawable.h"
namespace OGLE {
	static const VertexCollection s_QuadVertices = VertexCollection(
		{
			Vertex{ glm::vec2(-0.5,-0.5f), glm::vec4(1.0f), glm::vec2(-1.0f,-1.0f) },
			Vertex{ glm::vec2(-0.5, 0.5f), glm::vec4(1.0f), glm::vec2(-1.0f, 0.0f) },
			Vertex{ glm::vec2( 0.5, 0.5f), glm::vec4(1.0f), glm::vec2( 0.0f, 0.0f) },
			Vertex{ glm::vec2( 0.5,-0.5f), glm::vec4(1.0f), glm::vec2( 0.0f,-1.0f) }
		}
	);

	static const std::vector<GLushort> s_QuadIndices = {
		0, 1, 2,
		2, 3, 0
	};

	class Quad : public Drawable
	{
	public:
		Quad()
			: Drawable(new Mesh(s_QuadVertices, s_QuadIndices)) {}
		Quad(InstanceDataCollection instanceData)
			: Drawable(new InstancedMesh(s_QuadVertices, s_QuadIndices, instanceData)) {}
	};
}