#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	static VertexList s_QuadVertexList = VertexList(
		{
			{ glm::vec2(-0.5,-0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec2(-0.5, 0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f) },
			{ glm::vec2(0.5, 0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec2(0.5,-0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f) }
		}
	);

	static std::vector<GLushort> s_QuadIndices = 
	{
		0, 1, 2,
		2, 3, 0
	};

	static VertexCollection s_QuadVertices = VertexCollection(s_QuadVertexList, &s_QuadIndices);

	class Quad : public Shape
	{
	public:
		Quad
		(
			glm::vec3* position = new glm::vec3(0.0f),
			glm::vec3* rotDeg = new glm::vec3(0.0f),
			glm::vec3* scale = new glm::vec3(1.0f)
		)
			: Shape(s_QuadVertices, position, rotDeg, scale) {}
	};

	static const glm::vec3* cuboidQuadPositions[6]
	{
		new glm::vec3(0.0f, 0.0f, 0.5f),  // Front
		new glm::vec3(0.0f, 0.0f,-0.5f),  // Back
		new glm::vec3(-0.5f, 0.0f, 0.0f), // Left
		new glm::vec3(0.5f, 0.0f, 0.0f),  // Right
		new glm::vec3(0.0f,-0.5f, 0.0f),  // Bottom
		new glm::vec3(0.0f, 0.5f, 0.0f)   // Top
	};

	static const glm::vec3* cuboidQuadRotations[6]
	{	
		new glm::vec3(  0.0f,	0.0f, 0.0f), // Front
		new glm::vec3(  0.0f, 180.0f, 0.0f), // Back
		new glm::vec3(  0.0f,- 90.0f, 0.0f), // Left
		new glm::vec3(  0.0f,  90.0f, 0.0f), // Right
		new glm::vec3( 90.0f,   0.0f, 0.0f), // Bottom
		new glm::vec3(-90.0f,   0.0f, 0.0f)	 // Top
	};

	static const glm::mat4* cuboidQuadModelMatrices[6]
	{
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[0], *cuboidQuadRotations[0])),
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[1], *cuboidQuadRotations[1])),
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[2], *cuboidQuadRotations[2])),
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[3], *cuboidQuadRotations[3])),
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[4], *cuboidQuadRotations[4])),
		new glm::mat4(NewModelMatrix(*cuboidQuadPositions[5], *cuboidQuadRotations[5])),
	};

	static class QuadCuboid : public MultiShape
	{
	public:
		QuadCuboid(TextureGeometry* cuboidFaceTextures[6])
			: MultiShape
			(
				&s_QuadVertices,
				new InstanceList(
					{
						Instance(*cuboidQuadModelMatrices[0], *cuboidFaceTextures[0]),
						Instance(*cuboidQuadModelMatrices[1], *cuboidFaceTextures[1]),
						Instance(*cuboidQuadModelMatrices[2], *cuboidFaceTextures[2]),
						Instance(*cuboidQuadModelMatrices[3], *cuboidFaceTextures[3]),
						Instance(*cuboidQuadModelMatrices[4], *cuboidFaceTextures[4]),
						Instance(*cuboidQuadModelMatrices[5], *cuboidFaceTextures[5]),
					}
				)
			)
		{
		}
	};
}