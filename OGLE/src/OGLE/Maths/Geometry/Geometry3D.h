#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	class Cube : public Shape
	{
	public:
		Scope<VertexCollection> NewVertexCollection() override
		{
			constexpr std::array<Vertex, 24> cubeVertices = {
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

			constexpr std::array<GLushort, 36> cubeIndices = {
				0,  1,  2,  2,  3,  0,
				4,  5,  6,  6,  7,  4,
				8,  9, 10, 10, 11,  8,
				12, 13, 14, 14, 15, 12,
				16, 17, 18, 18, 19, 16,
				20, 21, 22, 22, 23, 20
			};

			return Shape::NewVertexCollection(cubeVertices, cubeIndices);
		}
	};


	

	//static const glm::mat4 cuboidQuadModelMatricessd[6]
	//{
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[0], cuboidQuadRotations[0])),
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[1], cuboidQuadRotations[1])),
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[2], cuboidQuadRotations[2])),
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[3], cuboidQuadRotations[3])),
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[4], cuboidQuadRotations[4])),
	//	glm::mat4(NewModelMatrix(cuboidQuadPositions[5], cuboidQuadRotations[5])),
	//};

	constexpr glm::vec3 cuboidQuadPositions[6]
	{
		glm::vec3(0.0f, 0.0f, 0.5f),  // Front
		glm::vec3(0.0f, 0.0f,-0.5f),  // Back
		glm::vec3(-0.5f, 0.0f, 0.0f),  // Left
		glm::vec3(0.5f, 0.0f, 0.0f),  // Right
		glm::vec3(0.0f,-0.5f, 0.0f),  // Bottom
		glm::vec3(0.0f, 0.5f, 0.0f)   // Top
	};

	constexpr glm::vec3 cuboidQuadRotations[6]
	{
		glm::vec3(0.0f, 180.0f, 0.0f), // Front
		glm::vec3(0.0f,   0.0f, 0.0f), // Back
		glm::vec3(0.0f,  90.0f, 0.0f), // Left
		glm::vec3(0.0f, -90.0f, 0.0f), // Right
		glm::vec3(-90.0f,   0.0f, 0.0f), // Bottom
		glm::vec3(90.0f,   0.0f, 0.0f)  // Top
	};


	// Precompute and store the model matrices for each quad at compile time
	constexpr std::array<glm::mat4, 6> cuboidQuadModelMatrices = {
		ConstModelMatrix(cuboidQuadPositions[0], cuboidQuadRotations[0]),
		ConstModelMatrix(cuboidQuadPositions[1], cuboidQuadRotations[1]),
		ConstModelMatrix(cuboidQuadPositions[2], cuboidQuadRotations[2]),
		ConstModelMatrix(cuboidQuadPositions[3], cuboidQuadRotations[3]),
		ConstModelMatrix(cuboidQuadPositions[4], cuboidQuadRotations[4]),
		ConstModelMatrix(cuboidQuadPositions[5], cuboidQuadRotations[5])
	};

	static std::array<Instance, 6>& NewQuadCuboid(glm::mat4 modelMatrix)
	{
		std::array<Instance, 6> faces;
		for (int i = 0; i < 6; i++)
			faces[i] = Instance(modelMatrix * cuboidQuadModelMatrices[i]);
		return faces;
	}

	static std::array<Instance, 6>& NewQuadCuboid(glm::vec3 position)
	{
		return NewQuadCuboid(NewModelMatrix(position));
	}

	class MultiQuad : public Quad
	{
	public:
		Scope<VertexCollection> NewVertexCollection() override
		{
			return Quad::NewVertexCollection();
		}

		static Scope<MultiQuad> Create(GLuint numQuadsMax, GLuint numQuadsMin = 0)
		{
			Scope<MultiQuad> multiQuad = Shape::Create<MultiQuad>();
			multiQuad->ReserveInstances(numQuadsMax, numQuadsMin);
			return multiQuad;
		}

		std::vector<Ref<Instance>>* GetQuadRefs(GLuint startIndex, GLuint length)
		{
			return m_Instances->GetSubset(startIndex, length, true);
		}
	};

	



}

