#pragma  once

#include "OGLE/MineClone/Block.h"
#include "OGLE/Display/Renderer/Model.h"

namespace OGLE {

	constexpr int CalculateMaxCompressedElementsSize(int c_chunkWidth, int c_buildHeight, int c_quadsInChunk) {
		// Calculate the total number of cubes in the chunk
		int totalCubes = c_chunkWidth * c_chunkWidth * c_buildHeight;

		// Calculate the maximum possible number of visible faces
		// Each cube has 6 faces, but faces adjacent to other cubes may be hidden
		// For the outer layer of cubes, all faces are potentially visible
		// For the inner layers, subtract the number of faces adjacent to solid blocks
		int c_maxVisibleQuads = totalCubes * 6 - ((c_chunkWidth - 2) * (c_chunkWidth - 2) * 4 * 6);

		// Return the maximum size of m_CompressedElements
		return c_maxVisibleQuads;
	}

	// Usage example
	constexpr GLuint c_chunkWidth = 16;
	constexpr GLfloat c_halfChunkWidth = GLfloat(c_chunkWidth) / 2.0f;
	constexpr GLuint c_buildHeight = 16;
	constexpr GLfloat c_halfBuildHeight = GLfloat(c_buildHeight) / 2.0f;

	constexpr GLuint c_BlocksInChunk = c_chunkWidth * c_buildHeight * c_chunkWidth;
	constexpr GLuint c_quadsInChunk = c_BlocksInChunk * 6;
	constexpr GLuint c_maxCulledQuads = ((c_chunkWidth - 1) * c_buildHeight + (c_buildHeight - 1) * c_chunkWidth) * c_chunkWidth * 2;
	constexpr GLuint c_maxVisibleQuads = c_quadsInChunk - c_maxCulledQuads;

	constexpr glm::vec3 c_ChunkCentre = glm::vec3(c_halfChunkWidth, c_halfBuildHeight, c_halfChunkWidth);
	constexpr glm::vec3 c_ChunkSize = glm::vec3(c_chunkWidth, c_buildHeight, c_chunkWidth);

	constexpr unsigned short CalculateRelChunkPos(const int x, const int y, const int z)
	{
		return x * c_buildHeight + y * c_chunkWidth + z;
	}

	constexpr unsigned short CalculateRelChunkPos(const glm::vec3& position)
	{
		return CalculateRelChunkPos(position.x, position.y, position.z);
	}

	constexpr std::array<BlockRefData, c_BlocksInChunk> CalculateBlockRefDataInChunk()
	{
		std::array<BlockRefData, c_BlocksInChunk> chunkBlockRefData{};
		for (unsigned short x = 0; x < c_chunkWidth; x++)
			for (unsigned short y = 0; y < c_buildHeight; y++)
				for (unsigned short z = 0; z < c_chunkWidth; z++)
				{
					glm::vec3 position(x, y, z);
					chunkBlockRefData[CalculateRelChunkPos(position)] = BlockRefData(position);
				}
		return chunkBlockRefData;
	}

	constexpr std::array<BlockRefData, c_BlocksInChunk> c_BlockRefDataInChunk = CalculateBlockRefDataInChunk();


	struct ChunkRefData
	{
		const int chunkX;
		const int chunkZ;

		ChunkRefData(int x, int z) : chunkX(x), chunkZ(z) {}

		ChunkRefData(const glm::vec2& position = glm::vec2())
			: ChunkRefData(position.x, position.y){}

		inline const BlockRefData& GetBlockRefData(glm::vec3& position) { return c_BlockRefDataInChunk[CalculateRelChunkPos(position)]; }
	};

	
	class Chunk : public AABB
	{
	public:
		Chunk(const glm::vec3& chunkPos, int chunkX, int chunkZ);

		void Load(std::vector<Ref<Instance>>* chunkAlloc);
		void Unload();

		Ref<Block> GetBlock(int x, int y, int z);

		std::vector<Ref<Block>> GetCollidingBlocks(const AABB& bounds)
		{
			std::vector<Ref<Block>> collidingBlocks;
			for (const Ref<Block>& block : m_ChunkBlocksOctree->query(bounds))
				collidingBlocks.emplace_back(block);
			return collidingBlocks;
		}

		Ref<Block> GetRaycastBlock(const Raycast& raycast)
		{
			return m_ChunkBlocksOctree->querySingle(raycast);
		}

		glm::vec2 GetChunkCoords();

		inline unsigned short GetX() { return m_ChunkRefData.chunkX; }
		inline unsigned short GetZ() { return m_ChunkRefData.chunkZ; }

	protected:
		friend class World;
		void ChunkUpdate();


	private:
		friend class WorldFileManager;
		std::vector< std::vector<std::vector<Ref<Block>>>> m_Blocks;
		Scope<Octree <Block>> m_ChunkBlocksOctree;
		ChunkRefData m_ChunkRefData;
	};

}
