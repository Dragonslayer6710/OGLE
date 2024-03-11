#include "oglepch.h"

#include "OGLE/MineClone/World.h"

namespace OGLE {

	World* World::s_CurrentWorld;

	World::World()
		: m_CentreCoords(glm::vec3(c_numBlocksOnAxis / 2, c_buildHeight / 2, c_numBlocksOnAxis / 2))
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
				glm::vec3 chunkMult = glm::vec3(chunkX, 0, chunkZ);
				glm::vec3 chunkPos = chunkMult * c_ChunkSize + c_ChunkCentre;

				m_Chunks[chunkX].push_back(CreateScope<Chunk>(chunkPos, chunkX, chunkZ));
		
				m_WorldChunksOctree->insert(m_Chunks[chunkX][chunkZ]);

			}
		}
		s_CurrentWorld = this;

		WorldUpdate();

		m_Player = std::move(Player::Create());
	}


	World::~World()
	{
	}

	Ref<Block> World::GetBlock(int x, int y, int z)	{		
		if (x < 0 || x >= c_numBlocksOnAxis || y < 0 || y >= c_buildHeight || z < 0 || z >= c_numBlocksOnAxis)
			return nullptr;
		glm::vec2 chunkCoords = GetChunkCoords(x, z);
		return m_Chunks[int(chunkCoords.x)][int(chunkCoords.y)]->GetBlock(x-chunkCoords.x*c_chunkWidth, y, z-chunkCoords.y*c_chunkWidth);
	}

	Ref<Block> World::GetBlock(float x, float y, float z) {
		return GetBlock(int(std::round(x)), int(std::round(y)), int(std::round(z)));
	}

	glm::vec2 World::GetChunkCoords(glm::vec3 position)
	{
		return GetChunkCoords(position.x, position.z);
	}

	glm::vec2 World::GetChunkCoords(int x, int z)
	{
		return glm::vec2((x * (c_numChunksOnAxis)) / (c_numBlocksOnAxis), (z * (c_numChunksOnAxis)) / (c_numBlocksOnAxis));
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

	glm::mat4 World::GetViewMatrix() const
	{
		return m_Player->GetViewMatrix();
	}

	void World::WorldUpdate()
	{
		for (std::vector<Ref<Chunk>> x : m_Chunks)
			for (Ref<Chunk> z : x)
				z->ChunkUpdate();
	}

	void World::LoadChunksInRange(int startX, int startZ, int endX, int endZ) {
		for (int chunkX = startX; chunkX <= endX; chunkX++) {
			for (int chunkZ = startZ; chunkZ <= endZ; chunkZ++) {
				// Check if the chunk exists in the loaded chunks vector
				bool chunkFound = false;
				for (const auto& chunk : m_LoadedChunks) {
					if (chunk->GetX() == chunkX && chunk->GetZ() == chunkZ) {
						chunkFound = true;
						break;
					}
				}

				// If the chunk is not found, attempt to load it from file
				if (!chunkFound) {
					glm::vec3 chunkMult = glm::vec3(chunkX, 0, chunkZ);
					glm::vec3 chunkPos = chunkMult * c_ChunkSize + c_ChunkCentre;
					Ref<Chunk> chunk = CreateScope<Chunk>(chunkPos, chunkX, chunkZ);
					if (m_WorldFileManager.LoadChunk(chunk)) {
						m_LoadedChunks.push_back(chunk);
					}
					else {
						// If loading from file fails, generate the chunk
						
					}
				}
			}
		}
	}

	void World::UnloadChunksInRange(int startX, int startZ, int endX, int endZ) {
		// Iterate through the loaded chunks vector and unload chunks within the specified range
		auto iter = std::remove_if(m_LoadedChunks.begin(), m_LoadedChunks.end(), [=](const Ref<Chunk>& chunk) {
			glm::vec2 chunkCoords = chunk->GetChunkCoords();
			return chunkCoords.x >= startX && chunkCoords.x <= endX && chunkCoords.y >= startZ && chunkCoords.y <= endZ;
			});
		m_LoadedChunks.erase(iter, m_LoadedChunks.end());
	}

	void World::SaveToFile(const std::string& filename) {
		// Use the WorldFileManager to save chunks to the file
		m_WorldFileManager.saveChunks(m_LoadedChunks);
	}

}