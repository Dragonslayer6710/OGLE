#include "oglepch.h"

#include "OGLE/MineClone/Chunk.h"
#include <random>

namespace OGLE {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> blockDist(0, 20);
	static int numChunks = 0;
	Chunk::Chunk(const glm::vec3& chunkPos, int chunkX, int chunkZ)
		: AABB(AABB::FromPos(chunkPos, c_ChunkSize)), m_ChunkRefData(chunkX, chunkZ)
	{
		m_ChunkBlocksOctree = CreateScope<Octree<Block>>(AABB::FromPos(c_ChunkCentre + c_ChunkSize*glm::vec3(chunkX, 0, chunkZ), c_ChunkSize));
		int worldX = chunkX * c_chunkWidth;
		int worldZ = chunkZ * c_chunkWidth;

		int blockID = 0;
		m_Blocks.reserve(c_chunkWidth); // Preallocate memory for x dimension
		for (int x = 0; x < c_chunkWidth; x++) {
			m_Blocks.push_back(std::vector<std::vector<Ref<Block>>>());
			m_Blocks[x].reserve(c_buildHeight); // Preallocate memory for y dimension

			for (int y = 0; y < c_buildHeight; y++) {
				m_Blocks[x].push_back(std::vector<Ref<Block>>());
				m_Blocks[x][y].reserve(c_chunkWidth); // Preallocate memory for z dimension

				for (int z = 0; z < c_chunkWidth; z++) {
					glm::vec3 pos = glm::vec3(x + worldX, y, z + worldZ);
					m_Blocks[x][y].push_back(Block::Create(pos, blockDist(gen)));
					m_ChunkBlocksOctree->insert(m_Blocks[x][y][z]);
					blockID += 6;
					// OGLE_CORE_INFO("Block {0} ({1}, {2}, {3}) Generated at Chunk {4}", m_Blocks[x][y][z]->GetWorldBlockID(), x + worldX, y, z + worldZ, numChunks + 1);
				}
			}
		}
		numChunks++;
	}

	void Chunk::Load(std::vector<Ref<Instance>>* chunkAlloc)
	{
		int blockIndex = 0;
		for (int x = 0; x < c_chunkWidth; x++)
			for (int y = 0; y < c_buildHeight; y++)
				for (int z = 0; z < c_chunkWidth; z++) {
					m_Blocks[x][y][z]->Load(
						std::vector<Ref<Instance>>(
							chunkAlloc->begin() + blockIndex,
							chunkAlloc->begin() + blockIndex + 6
						));
					blockIndex += 6;
				}
	}

	void Chunk::Unload()
	{
		for (const auto& xAxis : m_Blocks)
			for (const auto& xyPlane : xAxis)
				for (const Ref<Block>& block : xyPlane)
					block->Unload();
	}	

	Ref<Block> Chunk::GetBlock(int x, int y, int z)
	{
		return m_Blocks[x][y][z];
	}

	glm::vec2 Chunk::GetChunkCoords()
	{
		return glm::vec2();
	}

	void Chunk::ChunkUpdate()
	{
		std::vector<Shape> data = std::vector<Shape>();
		std::vector<Shape>* testData = &data;

		for (std::vector<std::vector<Ref<Block>>> x : m_Blocks)
			for (std::vector<Ref<Block>> y : x)
				for (Ref<Block> z : y)
					if (z != nullptr)
						z->UpdateGeometry();
		//OGLE_CORE_INFO("\nHidden Faces: {0}", Block::hiddenFaces);

	}

}