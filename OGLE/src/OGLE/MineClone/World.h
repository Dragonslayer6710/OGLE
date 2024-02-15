#pragma once
#include "OGLE/MineClone/Chunk.h"

namespace OGLE {

	class World
	{
	public:
		World();
		~World();

		Ref<MultiQuad> GetWorldGeometry();

		static Ref<Block> GetBlock(glm::vec3 position);
		
		static World* Get();

		void UpdateWorldGeometry();

	protected:
		friend class Block;
		std::vector<Instance>::iterator AddBlock(glm::vec3 position, std::vector<TextureGeometry> texGeoms);

		Ref<Block> GetBlock(int x, int y, int z);
		void HideFace(GLuint index);
		void ShowFace(GLuint index, Instance face);

	private:
		static World* s_CurrentWorld;

		std::vector<std::vector<Ref<Chunk>>> m_Chunks;
		Ref<MultiQuad> m_WorldGeometry = Shape::Create<MultiQuad>();
	};
}

