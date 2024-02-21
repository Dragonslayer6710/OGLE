#include "oglepch.h"

#include "OGLE/MineClone/World.h"

namespace OGLE {

	World* World::s_CurrentWorld;

	World::World()
	{
		if (Block::s_TextureAtlas == nullptr)
			Block::s_TextureAtlas = UniformTextureAtlas::Create("terrain.png", glm::vec2(16, 16));
		Block::ResetBlocks();

		// Preallocate memory for the m_Chunks vector
		m_Chunks.reserve(c_numChunksOnAxis);

		for (int chunkX = 0; chunkX < c_numChunksOnAxis; chunkX++) {
			m_Chunks.push_back(std::vector<Ref<Chunk>>());
			m_Chunks[chunkX].reserve(c_numChunksOnAxis); // Preallocate memory for the inner vector

			for (int chunkZ = 0; chunkZ < c_numChunksOnAxis; chunkZ++) {
				m_Chunks[chunkX].push_back(CreateScope<Chunk>(chunkX, chunkZ));
			}
		}
		s_CurrentWorld = this;
		WorldUpdate();
	}


	World::~World()
	{
		if (this != s_CurrentWorld)
			delete[] s_CurrentWorld;
		s_CurrentWorld = nullptr;
	}

	Ref<Block> World::GetBlock(int x, int y, int z)	{		
		if (x < 0 || x >= numBlocksOnAxis || y < 0 || y >= c_buildHeight || z < 0 || z >= numBlocksOnAxis)
			return nullptr;
		float chunkX = (x * (c_numChunksOnAxis)) / (numBlocksOnAxis);
		float chunkZ = (z * (c_numChunksOnAxis)) / (numBlocksOnAxis);
		return m_Chunks[int(chunkX)][int(chunkZ)]->GetBlock(x-chunkX*c_chunkWidth, y, z-chunkZ*c_chunkWidth);
	}

	Ref<Chunk> World::GetChunk(int chunkX, int chunkZ)
	{
		if (chunkX < 0 || chunkZ < 0 || chunkX >= c_numChunksOnAxis || chunkZ >= c_numChunksOnAxis)
			return nullptr;
		return s_CurrentWorld->m_Chunks[chunkX][chunkZ];
	}

	Ref<Block> World::GetBlock(glm::vec3 position)
	{		
		return s_CurrentWorld->GetBlock(position.x, position.y, position.z);
	}

	World* World::Get()
	{
		return s_CurrentWorld;
	}

	void World::WorldUpdate()
	{
		for (std::vector<Ref<Chunk>> x : m_Chunks)
			for (Ref<Chunk> z : x)
				z->ChunkUpdate();
	}
}