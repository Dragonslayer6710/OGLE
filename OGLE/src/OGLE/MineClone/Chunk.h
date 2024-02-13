#pragma  once

#include "OGLE/MineClone/Block.h"
namespace OGLE {
	class Window;

	static const GLuint numChunksOnAxis = 5;
	static const GLuint chunkWidth = 16;

	static const GLuint numBlocksOnAxis = numChunksOnAxis * chunkWidth;

	static const GLuint buildHeight = 16;

	class Chunk
	{
	public:
		Chunk(int chunkX, int chunkZ);

		Block* GetBlock(int x, int y, int z);
	protected:
		friend class World;
		void UpdateGeometry();

	private:
		std::vector< std::vector<std::vector<Block*>>> m_Blocks;
	};

}
