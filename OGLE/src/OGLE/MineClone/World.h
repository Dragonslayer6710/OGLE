#pragma once
#include "OGLE/MineClone/Chunk.h"

namespace OGLE {

	constexpr GLushort c_numChunksOnAxis = 2;
	constexpr GLuint numBlocksOnAxis = c_numChunksOnAxis * c_chunkWidth;

	class WorldRenderer;
	class World
	{
	public:
		static Ref<World> Create()
		{
			return CreateRef<World>();
		}

		World();
		~World();

		static Ref<Chunk> GetChunk(int chunkX, int chunkZ);

		static Ref<Block> GetBlock(glm::vec3 position);
		
		static World* Get();

		void WorldUpdate();

	protected:

		Ref<Block> GetBlock(int x, int y, int z);


	private:
		static World* s_CurrentWorld;

		std::vector<std::vector<Ref<Chunk>>> m_Chunks;

	};

	class WorldRenderer
	{
	public:
		WorldRenderer(GLushort renderDistance = c_numChunksOnAxis)
		{
			Init(renderDistance);
		}

		void NewOrigin(GLushort newOriginChunkX, GLushort newOriginChunkZ)
		{
			Init(m_RenderDistance, newOriginChunkX, newOriginChunkZ);
		}

		Ref<Model> GetWorldModel()
		{
			return m_WorldModel;
		}

	private:
		void Init(GLushort renderDistance, GLushort originChunkX = c_numChunksOnAxis/2, GLushort originChunkZ = c_numChunksOnAxis / 2)
		{
			if (renderDistance > m_RenderDistance)
				m_LoadedChunks.resize(renderDistance);

			GLushort renderDistanceHalf = renderDistance / 2;

			GLushort renderOriginChunk[2] = { originChunkX, originChunkZ };
			GLushort renderTopLeftChunk[2] = { originChunkX - renderDistanceHalf, originChunkZ - renderDistanceHalf };
			GLushort renderBottomRightChunk[2] = { originChunkX + renderDistanceHalf, originChunkZ + renderDistanceHalf };

			GLushort numChunks= 0;
			for (int chunkX = renderTopLeftChunk[0]; chunkX < renderBottomRightChunk[0]; chunkX++)
				for (int chunkZ = renderTopLeftChunk[1]; chunkZ < renderBottomRightChunk[1]; chunkZ++)
				{
					Ref<Chunk> chunk = World::GetChunk(chunkX, chunkZ);
					if (m_LoadedChunks[chunkX + m_RenderDistanceHalf].size() <= chunkZ + m_RenderDistanceHalf)
						m_LoadedChunks[chunkX + m_RenderDistanceHalf].push_back(chunk);
					else
					{
						if (m_LoadedChunks[chunkX + m_RenderDistanceHalf][chunkZ + m_RenderDistanceHalf] != nullptr) {
							m_LoadedChunks[chunkX + m_RenderDistanceHalf][chunkZ + m_RenderDistanceHalf]->Unload();
						}
						m_LoadedChunks[chunkX + m_RenderDistanceHalf][chunkZ + m_RenderDistanceHalf] = chunk;
					}
					if (chunk != nullptr)
						numChunks += 1;
				}
			if (m_NumChunks != numChunks)
				m_WorldQuads = MultiQuad::Create(numChunks * c_quadsInChunk, numChunks * c_maxVisibleQuads);

			m_NumChunks = numChunks;
			m_RenderDistance = renderDistance;
			m_RenderDistanceHalf = renderDistanceHalf;

			m_RenderOriginChunk = renderOriginChunk;
			m_RenderTopLeftChunk = renderTopLeftChunk;
			m_RenderBottomRightChunk = renderBottomRightChunk;
			LoadChunks();
		}

		void LoadChunks()
		{
			int chunkIndex = 0;
			for (int chunkX = 0; chunkX < m_RenderDistance; chunkX++)
				for (int chunkZ = 0; chunkZ < m_RenderDistance; chunkZ++)
				{
					Ref<Chunk> chunk = m_LoadedChunks[chunkX][chunkZ];
					if (chunk != nullptr) {
						chunk->Load(m_WorldQuads->GetQuadRefs(chunkIndex, c_quadsInChunk));
						chunkIndex += c_quadsInChunk;
					}
				}
			m_WorldMesh = Mesh::Create(m_WorldQuads);
			m_WorldModel = Model::Create(m_WorldMesh, Block::s_TextureAtlas);
		}

	private:
		GLushort m_NumChunks = 0;
		GLushort m_RenderDistance = 0;
		GLushort m_RenderDistanceHalf = 0;

		GLushort* m_RenderOriginChunk;
		GLushort* m_RenderTopLeftChunk;
		GLushort* m_RenderBottomRightChunk;

		std::vector<std::vector<Ref<Chunk>>> m_LoadedChunks;

		Ref<MultiQuad> m_WorldQuads;
		Ref<Mesh> m_WorldMesh;
		Ref<Model> m_WorldModel;
	};

}

