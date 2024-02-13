#include "oglepch.h"

#include "OGLE/MineClone/World.h"

namespace OGLE {

	World* World::s_CurrentWorld = nullptr;
	void World::AddBlock(glm::vec3 position, std::vector<TextureGeometry> texGeoms)
	{
	    m_WorldGeometry->AddInstances(NewQuadCuboid(NewModelMatrix(position), texGeoms));
		//m_WorldGeometry->AddInstances(std::initializer_list(s_QuadCuboidQuadInstances));
	}

	World::World()
	{

		World::s_CurrentWorld = this;
		for (int chunkX = 0; chunkX < numChunksOnAxis; chunkX++) {
			m_Chunks.push_back(std::vector<Chunk*>());
			for (int chunkZ = 0; chunkZ < numChunksOnAxis; chunkZ++)
				m_Chunks[chunkX].push_back(new Chunk(chunkX, chunkZ));
		}
		UpdateWorldGeometry();
	}

	MultiQuad* World::GetWorldGeometry()
	{
		return m_WorldGeometry;
	}

	Block* World::GetBlock(int x, int y, int z)	{	
		int chunkX = x / (chunkWidth * numChunksOnAxis);
		int chunkZ = z / (chunkWidth * numChunksOnAxis);
		if (x < 0 || x >= numBlocksOnAxis || y < 0 || y >= buildHeight || z < 0 || z >= numBlocksOnAxis)
			return nullptr;
		return m_Chunks[chunkX][chunkZ]->GetBlock(x/numBlocksOnAxis* chunkWidth, y, z / numBlocksOnAxis * chunkWidth);
	}

	Block* World::GetBlock(glm::vec3 position)
	{		
		return s_CurrentWorld->GetBlock(position.x, position.y, position.z);
	}

	World* World::Get()
	{
		return s_CurrentWorld;
	}

	void World::UpdateWorldGeometry()
	{
		for (std::vector<Chunk*> x : m_Chunks)
			for (Chunk* z : x)
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