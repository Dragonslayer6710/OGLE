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
		Quad()
			: Shape(&s_QuadVertices) {}
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

	static InstanceList* NewQuadCuboidInstanceList(Texture* texture = nullptr, GLushort subTextureIDs[] = nullptr, glm::mat4 modelMatrix = glm::mat4(1.0f))
	{
		std::vector<Instance>* instances = new std::vector<Instance>();
		TextureGeometry* texGeom;
		for (int side = 0; side < 6; side++) {
			if (texture != nullptr && !texture->IsAtlas())
			{
				OGLE_CORE_ASSERT(subTextureIDs != nullptr, "QuadCuboid Error: TextureAtlas provided without sub texture ids");
				texGeom = &((TextureAtlas*)texture)->GetSubTexture(subTextureIDs[side]);
			}
			else
				texGeom = new TextureGeometry();
			glm::mat4 finalMatrix = modelMatrix * *cuboidQuadModelMatrices[side];

			instances->push_back(Instance(finalMatrix, *texGeom));
		}
		return new InstanceList(instances);
	}

	class QuadCuboid : public MultiShape
	{
	public:
		static QuadCuboid* Create(Texture* texture = nullptr, GLushort subTextureIDs[] = nullptr, glm::mat4 modelMatrix = glm::mat4(1.0f), DataLayout instanceLayout = s_DefInstanceLayout) {
			return new QuadCuboid(
				new InstanceCollection(*NewQuadCuboidInstanceList(texture, subTextureIDs, modelMatrix), instanceLayout)
			);
		}
	protected:
		QuadCuboid(InstanceCollection* instances)
			: MultiShape
			(
				&s_QuadVertices,
				instances
			)
		{
		}
	};
}