#include "oglepch.h"

#include "OGLE/MineClone/World.h"

namespace OGLE {

	World* World::s_CurrentWorld = nullptr;
	std::vector<Instance>::iterator World::AddBlock(glm::vec3 position, std::vector<TextureGeometry> texGeoms)
	{
	    m_WorldGeometry->AddInstances(NewQuadCuboid(NewModelMatrix(position), texGeoms));
		return m_WorldGeometry->GetInstances()->GetElements()->begin();
		//m_WorldGeometry->AddInstances(std::initializer_list(s_QuadCuboidQuadInstances));
	}
	World::World()
	{
		if (Block::s_TextureAtlas == nullptr)
			Block::s_TextureAtlas = UniformTextureAtlas::Create("terrain.png", glm::vec2(16, 16));
		Block::ResetBlocks();
		World::s_CurrentWorld = this;
		for (int chunkX = 0; chunkX < numChunksOnAxis; chunkX++) {
			m_Chunks.push_back(std::vector<Ref<Chunk>>());
			for (int chunkZ = 0; chunkZ < numChunksOnAxis; chunkZ++)
				m_Chunks[chunkX].push_back(CreateScope<Chunk>(chunkX, chunkZ));
		}
		UpdateWorldGeometry();
	}


	World::~World()
	{
		s_CurrentWorld = nullptr;
	}

	Ref<MultiQuad> World::GetWorldGeometry()
	{
		return m_WorldGeometry;
	}

	Ref<Block> World::GetBlock(int x, int y, int z)	{		
		if (x < 0 || x >= numBlocksOnAxis || y < 0 || y >= buildHeight || z < 0 || z >= numBlocksOnAxis)
			return nullptr;
		float chunkX = (x * (numChunksOnAxis)) / (numBlocksOnAxis);
		float chunkZ = (z * (numChunksOnAxis)) / (numBlocksOnAxis);
		return m_Chunks[int(chunkX)][int(chunkZ)]->GetBlock(x-chunkX*chunkWidth, y, z-chunkZ*chunkWidth);
	}

	Ref<Block> World::GetBlock(glm::vec3 position)
	{		
		return s_CurrentWorld->GetBlock(position.x, position.y, position.z);
	}

	World* World::Get()
	{
		return s_CurrentWorld;
	}

	void World::UpdateWorldGeometry()
	{
		for (std::vector<Ref<Chunk>> x : m_Chunks)
			for (Ref<Chunk> z : x)
					z->UpdateGeometry();
	}

	void World::HideFace(GLuint index)
	{
		m_WorldGeometry->RemoveInstance(index);
	}

	void World::ShowFace(GLuint index, Instance face)
	{
		m_WorldGeometry->InsertInstance(index, face);
	}

}