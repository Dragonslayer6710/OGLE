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
			glm::vec3* scale = new glm::vec3(1.0f),
			TextureGeometry* texGeom = new TextureGeometry()
		)
			: Shape(s_QuadVertices, position, rotDeg, scale, texGeom) {}
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
		new glm::vec3(-90.0f,   0.0f, 0.0f), // Bottom
		new glm::vec3( 90.0f,   0.0f, 0.0f)	 // Top
	};

	static struct QuadCuboid : MultiShape
	{

		QuadCuboid(TextureGeometry* cuboidQuadTexGeoms[6] = nullptr)
		{
			std::vector<Shape*> quads;
			for (int i = 0; i < 6; i++)
			{
				TextureGeometry* texGeom;
				if (cuboidQuadTexGeoms != nullptr)
					texGeom = cuboidQuadTexGeoms[i];
				else
					texGeom = new TextureGeometry();

				glm::vec3* pos = new glm::vec3(*cuboidQuadPositions[i]);
				glm::vec3* rot = new glm::vec3(*cuboidQuadRotations[i]);

				quads.push_back(new Quad(pos, rot, new glm::vec3(1.0f), texGeom));
			}
			RegisterShapes(quads);
			PrepareMeshData();
		}
	};
}