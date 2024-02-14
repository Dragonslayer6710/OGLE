#include "oglepch.h"

#include "OGLE/MineClone/Chunk.h"
#include <random>

namespace OGLE {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> blockDist(-1, 3);
	static int numChunks = 0;
	Chunk::Chunk(int chunkX, int chunkZ)
	{
		int worldX = chunkX * chunkWidth;
		int worldZ = chunkZ * chunkWidth;

		for (int x = 0; x < chunkWidth; x++) {
			m_Blocks.push_back(std::vector<std::vector<Ref<Block>>>());
			for (int y = 0; y < buildHeight; y++) {
				m_Blocks[x].push_back(std::vector<Ref<Block>>());
				for (int z = 0; z < chunkWidth; z++)
				{
					m_Blocks[x][y].push_back(CreateRef<Block>(glm::vec3(x + worldX, y, z + worldZ), blockDist(gen)));
					//OGLE_CORE_INFO("Block {0} ({1}, {2}, {3}) Generated at Chunk {4}", m_Blocks[x][y][z]->GetWorldBlockID(), x + worldX, y, z + worldZ, numChunks + 1);
				}
			}
		}

		numChunks++;

	}

	Ref<Block> Chunk::GetBlock(int x, int y, int z)
	{
		return m_Blocks[x][y][z];
	}

	void Chunk::UpdateGeometry()
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