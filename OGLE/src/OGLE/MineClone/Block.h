#pragma once

#include "OGLE/Maths/Geometry/Geometry3D.h"
#include "OGLE/Physics/Physics.h"

constexpr glm::vec3 c_BlockSize = glm::vec3(1.0f);
constexpr glm::vec3 c_BlockHalfSize = c_BlockSize / 2.0f;
constexpr glm::vec3 c_BlockHalfSizeNegative = c_BlockHalfSize;

struct BlockRefData
{
	const glm::vec3 BlockPos;
	const glm::vec3 BlockMin;
	const glm::vec3 BlockMax;

	// Constructor with default values for its arguments
	constexpr BlockRefData(const glm::vec3& position = glm::vec3(0.0f))
		: BlockPos(position),
		BlockMin(position + c_BlockHalfSizeNegative),
		BlockMax(position + c_BlockHalfSize)
	{}

	constexpr BlockRefData operator=(const BlockRefData& other) const
	{
		return BlockRefData(other.BlockPos);
	}
};

namespace OGLE {
	class World;

	static enum BlockSide {
		BlockSouth,
		BlockNorth,
		BlockWest,
		BlockEast,
		BlockBottom,
		BlockTop
	};

	class Chunk;
	class World;

	class Block : public AABB
	{
	public:
		static Ref<Block> Create(glm::vec3 position, GLushort id = 2)
		{
			return CreateRef<Block>(position, id);
		}

		void Load(std::vector<Ref<Instance>>& blockAlloc);
		void Unload();

		Block(const glm::vec3& position, GLushort id = 2);

		void UpdateGeometry();

		void HideFace(int face);

		void ShowFace(int face);

		glm::vec3 GetPos() { return AABB::getCenter(); }

		GLushort GetBlockID();

		GLuint Block::GetBlockInstanceID();

		static void ResetBlocks() {
			numBlocks = 0;
		}

		static Ref<TextureAtlas> s_TextureAtlas;

	private:
		glm::vec3 m_Position;
		glm::mat4 m_ModelTransform;
		GLushort m_BlockID;
		GLuint m_BlockInstanceID = numBlocks++;

		std::array<Instance, 6> m_Faces;

		std::array<Ref<Instance>, 6> m_LoadedFaces;
		std::array<Instance, 6> m_HiddenFaces;

		static GLuint numBlocks;

		void MapTexture();

	};
}
