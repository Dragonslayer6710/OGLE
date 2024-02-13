#include "oglepch.h"

#include "OGLE/MineClone/Chunk.h"


namespace OGLE {
	static int numChunks = 0;
	Chunk::Chunk(int chunkX, int chunkZ)
	{
		int worldX = chunkX * chunkWidth;
		int worldZ = chunkZ * chunkWidth;
		for (int y = 0; y < buildHeight; y++) 
			for (int x = 0; x < chunkWidth; x++) 
				for (int z = 0; z < chunkWidth; z++)
				{
					if (y==0)
						m_Blocks.push_back(std::vector<std::vector<Block*>>());
					if (z == 0)
						m_Blocks[x].push_back(std::vector<Block*>());
					m_Blocks[x][y].push_back(new Block(glm::vec3(x+worldX, y, z+worldZ)));
					//OGLE_CORE_INFO("Block {0} ({1}, {2}, {3}) Generated at Chunk {4}", m_Blocks[x][y][z]->GetWorldBlockID(), x + worldX, y, z + worldZ, numChunks + 1);
				}
		numChunks++;

	}

	OGLE::Block* Chunk::GetBlock(int x, int y, int z)
	{
		return m_Blocks[x][y][z];
	}

	void Chunk::UpdateGeometry()
	{
		std::vector<Shape> data = std::vector<Shape>();
		std::vector<Shape>* testData = &data;

		for (std::vector<std::vector<Block*>> x : m_Blocks)
			for (std::vector<Block*> y : x)
				for (Block* z : y)
					z->UpdateGeometry();
		//OGLE_CORE_INFO("\nHidden Faces: {0}", Block::hiddenFaces);

	}

}