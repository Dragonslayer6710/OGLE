#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE {

	class Cuboid : public Shape
	{
	public:
		Cuboid(const glm::vec3& dimensions, const glm::vec4& color = glm::vec4(1.0f))
			: m_Dimensions(dimensions), m_Color(color) {}

		Scope<VertexCollection> NewVertexCollection() override
		{
			float halfWidth = m_Dimensions.x / 2.0f;
			float halfHeight = m_Dimensions.y / 2.0f;
			float halfDepth = m_Dimensions.z / 2.0f;

			std::array<Vertex, 8> cuboidVertices = {
				Vertex(glm::vec3(-halfWidth,-halfHeight, halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3( halfWidth,-halfHeight, halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3( halfWidth, halfHeight, halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3(-halfWidth, halfHeight, halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3(-halfWidth,-halfHeight,-halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3( halfWidth,-halfHeight,-halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3( halfWidth, halfHeight,-halfDepth), m_Color, glm::vec2()),
				Vertex(glm::vec3(-halfWidth, halfHeight,-halfDepth), m_Color, glm::vec2())
			};

			constexpr std::array<GLushort, 36> cuboidIndices = {
				// Front face
				0, 1, 2, 2, 3, 0,
				// Back face
				5, 4, 7, 7, 6, 5,
				// Top face
				3, 2, 6, 6, 7, 3,
				// Bottom face
				4, 5, 1, 1, 0, 4,
				// Right face
				1, 5, 6, 6, 2, 1,
				// Left face
				4, 0, 3, 3, 7, 4
			};

			return Shape::NewVertexCollection(cuboidVertices, cuboidIndices);
		}

		static Scope<Cuboid> Create(GLuint numCuboids, const glm::vec3& dimensions, const glm::vec4& color = glm::vec4(1.0f))
		{
			Scope<Cuboid> cuboid = CreateScope<Cuboid>(dimensions, color);
			cuboid->SetVertexCollection();
			cuboid->ReserveInstances(numCuboids);
			return cuboid;
		}

		std::vector<Ref<Instance>>* GetCuboidRefs(GLuint startIndex, GLuint length)
		{
			return m_Instances->GetSubset(startIndex, length, true);
		}

	protected:
		glm::vec3 m_Dimensions;
		glm::vec4 m_Color;
	};

	class Cube : public Cuboid
	{
		Cube(const GLfloat size, const glm::vec4 color = glm::vec4(1.0f)) : Cuboid(glm::vec3(size), color) {}	};

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

