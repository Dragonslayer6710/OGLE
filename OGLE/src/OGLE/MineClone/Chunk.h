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
	constexpr GLuint c_buildHeight = 16;
	constexpr GLuint c_quadsInChunk = c_chunkWidth * c_buildHeight * c_chunkWidth * 6;
	constexpr GLuint c_maxCulledQuads = ((c_chunkWidth - 1) * c_buildHeight + (c_buildHeight - 1) * c_chunkWidth) * c_chunkWidth * 2;
	constexpr GLuint c_maxVisibleQuads = c_quadsInChunk - c_maxCulledQuads;
	
	class Chunk
	{
	public:
		Chunk(int chunkX, int chunkZ);

		void Load(std::vector<Ref<Instance>>* chunkAlloc);
		void Unload();

		Ref<Block> GetBlock(int x, int y, int z);
	protected:
		friend class World;
		void ChunkUpdate();

	private:
		std::vector< std::vector<std::vector<Ref<Block>>>> m_Blocks;
	};

}
