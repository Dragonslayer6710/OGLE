#pragma once

#include "OGLE/MineClone/Chunk.h"
#include "OGLE/MineClone/Player.h"

namespace OGLE {

	constexpr GLushort c_ExtraHorizontalChunks = 1;
	constexpr GLushort c_numChunksOnAxis = 1 + 2 * c_ExtraHorizontalChunks;
	constexpr GLuint c_numBlocksOnAxis = c_numChunksOnAxis * c_chunkWidth;
	constexpr GLfloat c_halfNumBlocksOnAxis = GLfloat(c_numBlocksOnAxis) / 2.0f;

	constexpr glm::vec3 c_WorldCentre = glm::vec3(c_halfNumBlocksOnAxis, c_halfBuildHeight, c_halfNumBlocksOnAxis);
	constexpr glm::vec3 c_WorldSize = glm::vec3(c_numBlocksOnAxis, c_buildHeight, c_numBlocksOnAxis);

	struct CollisionData
	{
		bool grounded = false;
		glm::vec3 revertCollision = glm::vec3();
	};

	class WorldRenderer;

	class WorldFileManager {
	private:
		std::string m_filename;
		glm::vec2 m_playerPos;

		void serializeChunkRefData(std::ofstream& file, const ChunkRefData& chunkRef) const {
			int relativeX = chunkRef.chunkX - static_cast<int>(m_playerPos.x);
			int relativeZ = chunkRef.chunkZ - static_cast<int>(m_playerPos.y);
			ChunkRefData relativeChunkRef{ relativeX, relativeZ };
			file.write(reinterpret_cast<const char*>(&relativeChunkRef), sizeof(ChunkRefData));
		}

		ChunkRefData deserializeChunkRefData(std::ifstream& file) const {
			ChunkRefData chunkRef;
			file.read(reinterpret_cast<char*>(&chunkRef), sizeof(ChunkRefData));
			int absoluteX = chunkRef.chunkX + static_cast<int>(m_playerPos.x);
			int absoluteZ = chunkRef.chunkZ + static_cast<int>(m_playerPos.y);
			return ChunkRefData{ absoluteX, absoluteZ }; // Create a new ChunkRefData object
		}

	public:
		WorldFileManager(const std::string& filename, const glm::vec2& playerPos)
			: m_filename(filename), m_playerPos(playerPos) {}

		bool LoadChunk(Ref<Chunk> chunk) const {
			std::ifstream file(m_filename, std::ios::binary);
			// Logic to load chunk data from file into 'chunk'
			if (file.good()) {
				// Read data from file and populate 'chunk'
				// For example:
				// file.read(reinterpret_cast<char*>(&chunk->x), sizeof(int));
				// file.read(reinterpret_cast<char*>(&chunk->z), sizeof(int));
				return true; // Return true if loading is successful
			}
			else {
				// Handle file not found or other errors
				return false; // Return false if loading fails
			}
		}

		void saveChunks(const std::vector<Ref<Chunk>>& chunks) const {
			std::vector<ChunkRefData> chunkRefs;
			for (const auto& chunk : chunks) {
				chunkRefs.emplace_back(chunk->GetX(), chunk->GetZ());
			}
			saveChunksToFile(chunkRefs);
		}

		std::vector<Chunk> loadChunks() const {
			// Load ChunkRefData from file
			std::vector<ChunkRefData> chunkRefs;
			std::ifstream file(m_filename, std::ios::binary);
			while (file.good()) {
				ChunkRefData chunkRef = deserializeChunkRefData(file);
				chunkRefs.push_back(chunkRef);
			}

			// Convert ChunkRefData to Chunk
			std::vector<Chunk> chunks;
			for (const auto& chunkRef : chunkRefs) {
				// You might need to populate other data in Chunk here
				glm::vec3 chunkMult = glm::vec3(chunkRef.chunkX, 0, chunkRef.chunkZ);
				glm::vec3 chunkPos = chunkMult * c_ChunkSize + c_ChunkCentre;
				chunks.push_back(Chunk(chunkPos, chunkRef.chunkX, chunkRef.chunkZ));
			}

			return chunks;
		}

	private:
		void saveChunksToFile(const std::vector<ChunkRefData>& chunks) const {
			std::ofstream file(m_filename, std::ios::binary);
			for (const auto& chunk : chunks) {
				// Write data from 'chunk' to file
				file.write(reinterpret_cast<const char*>(&chunk), sizeof(ChunkRefData));
			}
		}
	};

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

		static glm::vec2 GetChunkCoords(glm::vec3 position);

		static glm::vec2 GetChunkCoords(int x, int z);

		std::vector<Ref<Chunk>> GetCollidingChunks(const AABB& bounds)
		{
			std::vector<Ref<Chunk>> collidingChunks;
			for (const Ref<Chunk>& chunk : m_WorldChunksOctree->query(bounds))
				collidingChunks.emplace_back(chunk);
			return collidingChunks;
		}

		std::vector<Ref<Block>> GetCollidingBlocks(const AABB& bounds)
		{
			std::vector<Ref<Block>> collidingBlocks;
			for (const Ref<Chunk>& chunk : GetCollidingChunks(bounds))
				for (const Ref<Block>& block : chunk->GetCollidingBlocks(bounds))
					collidingBlocks.emplace_back(block);
			return collidingBlocks;
		}

		static glm::vec3 CentreCoords(glm::vec3 pos)
		{
			return pos - s_CurrentWorld->m_CentreCoords;
		}

		static glm::vec3 DecentreCoords(glm::vec3 pos = glm::vec3(0.0f))
		{
			return pos + s_CurrentWorld->m_CentreCoords;
		}


		Ref<Player> GetPlayer() { return m_Player; }

		glm::mat4 GetViewMatrix() const;

		void WorldUpdate();

		// Method to load chunks within a certain range
		void LoadChunksInRange(int startX, int startZ, int endX, int endZ);

		// Method to unload chunks within a certain range
		void UnloadChunksInRange(int startX, int startZ, int endX, int endZ);

		// Method to save the world to file
		void SaveToFile(const std::string& filename);

		// Method to load the world from file
		void LoadFromFile(const std::string& filename);

		// Method to obtain references to loaded chunks
		std::vector<Ref<Chunk>>& GetLoadedChunks() {
			return m_LoadedChunks;
		}

	protected:

		Ref<Block> GetBlock(int x, int y, int z);

		Ref<Block> GetBlock(float x, float y, float z);


	private:
		WorldFileManager m_WorldFileManager = WorldFileManager("testWorldFile.world", glm::vec2(0.0f));
		static World* s_CurrentWorld;

		Ref<Player> m_Player;

		const glm::vec3 m_CentreCoords;

		std::vector<std::vector<Ref<Chunk>>> m_Chunks;

		Scope<Octree <Chunk>> m_WorldChunksOctree = CreateScope<Octree<Chunk>>(AABB::FromPos(c_WorldCentre, c_WorldSize));

		// Additional member to store loaded chunks
		std::vector<Ref<Chunk>> m_LoadedChunks;
	};



	class WorldRenderer {
	public:
		WorldRenderer(Ref<World> world, GLushort renderDistance = c_numChunksOnAxis)
			: m_World(world), m_RenderDistance(renderDistance) {
			Init();
		}

		~WorldRenderer() {
			UnloadChunks();
		}

		Ref<Model> GetWorldModel() const {
			return m_WorldModel;
		}

	private:
		Ref<World> m_World;
		GLushort m_RenderDistance;
		std::vector<Ref<Chunk>> m_LoadedChunks;
		Ref<MultiQuad> m_WorldQuads;
		Ref<Mesh> m_WorldMesh;
		Ref<Model> m_WorldModel;

		// Method to initialize the world renderer
		void Init() {
			// Calculate the maximum number of quads based on the render distance and other parameters
			GLsizei maxQuads = m_RenderDistance * m_RenderDistance * c_maxVisibleQuads;

			// Create the world quads with the correct size and configuration
			m_WorldQuads = MultiQuad::Create(maxQuads, maxQuads);

			// Resize the loaded chunks vector to the appropriate size
			m_LoadedChunks.resize(m_RenderDistance * m_RenderDistance);

			int chunkIndex = 0;

			// Iterate over the chunks within the render distance
			for (int chunkX = 0; chunkX < m_RenderDistance; chunkX++) {
				for (int chunkZ = 0; chunkZ < m_RenderDistance; chunkZ++) {
					// Get the chunk from the world
					Ref<Chunk> chunk = m_World->GetChunk(chunkX, chunkZ);
					if (chunk) {
						// Load the chunk into the renderer
						m_LoadedChunks[chunkX * m_RenderDistance + chunkZ] = chunk;
						if (chunk != nullptr) {
							chunk->Load(m_WorldQuads->GetQuadRefs(chunkIndex, c_quadsInChunk));
							chunkIndex += c_quadsInChunk;
						}
						// Perform any additional setup for the loaded chunk
					}
				}
			}


			// Create the world mesh using the world quads
			m_WorldMesh = Mesh::Create(m_WorldQuads);

			// Create the world model using the world mesh and any other required parameters
			m_WorldModel = Model::Create(m_WorldMesh, Block::s_TextureAtlas);
		}

		// Method to unload all loaded chunks
		void UnloadChunks() {
			// Clear the loaded chunks vector
			m_LoadedChunks.clear();
		}

	};

	class WorldRendererOld
	{
	public:
		WorldRendererOld(GLushort renderDistance = c_numChunksOnAxis)
		{
			Init(renderDistance);
		}

		~WorldRendererOld()
		{
			m_WorldModel->MFD();
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
		void Init(GLushort renderDistance, GLushort originChunkX = (c_numChunksOnAxis + 1) / 2, GLushort originChunkZ = (c_numChunksOnAxis + 1) / 2)
		{
			if (renderDistance > m_RenderDistance)
				m_LoadedChunks.resize(renderDistance);

			GLfloat renderDistanceHalf = renderDistance / 2.0f;

			GLushort renderOriginChunk[2] = { originChunkX, originChunkZ };
			GLushort renderTopLeftChunk[2] = { originChunkX - renderDistanceHalf, originChunkZ - renderDistanceHalf };
			GLushort renderBottomRightChunk[2] = { originChunkX + renderDistanceHalf, originChunkZ + renderDistanceHalf };

			GLushort numChunks = 0;
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
		GLfloat m_RenderDistanceHalf = 0;

		GLushort* m_RenderOriginChunk;
		GLushort* m_RenderTopLeftChunk;
		GLushort* m_RenderBottomRightChunk;

		std::vector<std::vector<Ref<Chunk>>> m_LoadedChunks;

		Ref<MultiQuad> m_WorldQuads;
		Ref<Mesh> m_WorldMesh;
		Ref<Model> m_WorldModel;
	};

	
}
