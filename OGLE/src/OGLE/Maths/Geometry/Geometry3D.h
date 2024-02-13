#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	static const std::initializer_list<Vertex> s_CubeVertices
	{
		Vertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //0 Right
		Vertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //1
		Vertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //2
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)), //3

		Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //4 Left
		Vertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //5
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //6
		Vertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)), //7

		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //8 Top
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //9
		Vertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //10
		Vertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)), //11

		Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //12 Bottom
		Vertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //13
		Vertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //14
		Vertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)), //15	

		Vertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //16 Front
		Vertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //17
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //18
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)), //19

		Vertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)), //20 Back
		Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)), //21
		Vertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)), //22
		Vertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f))  //23
	};

	static const std::vector<GLushort> s_CubeIndices
	{
		 0,  1,  2,
		 2,  3,  0,

		 4,  5,  6,
		 6,  7,  4,

		8,  9, 10,
		10, 11,  8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	class Cube : public Shape
	{
	public:
		VertexCollection* NewVertexCollection() override
		{
			return Shape::NewVertexCollection(s_CubeVertices, s_CubeIndices);
		}
	};

	static const glm::vec3 cuboidQuadPositions[6]
	{
		glm::vec3( 0.0f, 0.0f, 0.5f),  // Front
		glm::vec3( 0.0f, 0.0f,-0.5f),  // Back
		glm::vec3(-0.5f, 0.0f, 0.0f),  // Left
		glm::vec3( 0.5f, 0.0f, 0.0f),  // Right
		glm::vec3( 0.0f,-0.5f, 0.0f),  // Bottom
		glm::vec3( 0.0f, 0.5f, 0.0f)   // Top
	};

	static const glm::vec3 cuboidQuadRotations[6]
	{
		glm::vec3(  0.0f,	0.0f, 0.0f), // Front
		glm::vec3(  0.0f, 180.0f, 0.0f), // Back
		glm::vec3(  0.0f,- 90.0f, 0.0f), // Left
		glm::vec3(  0.0f,  90.0f, 0.0f), // Right
		glm::vec3( 90.0f,   0.0f, 0.0f), // Bottom
		glm::vec3(-90.0f,   0.0f, 0.0f)	 // Top
	};

	static const glm::mat4 cuboidQuadModelMatrices[6]
	{
		glm::mat4(NewModelMatrix(cuboidQuadPositions[0], cuboidQuadRotations[0])),
		glm::mat4(NewModelMatrix(cuboidQuadPositions[1], cuboidQuadRotations[1])),
		glm::mat4(NewModelMatrix(cuboidQuadPositions[2], cuboidQuadRotations[2])),
		glm::mat4(NewModelMatrix(cuboidQuadPositions[3], cuboidQuadRotations[3])),
		glm::mat4(NewModelMatrix(cuboidQuadPositions[4], cuboidQuadRotations[4])),
		glm::mat4(NewModelMatrix(cuboidQuadPositions[5], cuboidQuadRotations[5])),
	};

	static const std::vector<Instance> s_QuadCuboidQuadInstances
	{
		Instance(cuboidQuadModelMatrices[0]),
		Instance(cuboidQuadModelMatrices[1]),
		Instance(cuboidQuadModelMatrices[2]),
		Instance(cuboidQuadModelMatrices[3]),
		Instance(cuboidQuadModelMatrices[4]),
		Instance(cuboidQuadModelMatrices[5]),
	};

	static std::vector<Instance> NewQuadCuboid(glm::mat4 modelMatrix, std::vector<TextureGeometry> texGeoms)
	{
		return std::vector<Instance>
		{
			Instance(modelMatrix * cuboidQuadModelMatrices[0], texGeoms[0]),
			Instance(modelMatrix * cuboidQuadModelMatrices[1], texGeoms[1]),
			Instance(modelMatrix * cuboidQuadModelMatrices[2], texGeoms[2]),
			Instance(modelMatrix * cuboidQuadModelMatrices[3], texGeoms[3]),
			Instance(modelMatrix * cuboidQuadModelMatrices[4], texGeoms[4]),
			Instance(modelMatrix * cuboidQuadModelMatrices[5], texGeoms[5])
		};
	}

	class MultiQuad : public Quad
	{
	public:
		VertexCollection* NewVertexCollection() override
		{
			return Quad::NewVertexCollection();
		}
	};

	



}

