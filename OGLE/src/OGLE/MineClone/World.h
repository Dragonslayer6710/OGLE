#pragma once

#include "OGLE/MineClone/Chunk.h"

namespace OGLE {

	class World
	{
	public:
		World();

		MultiQuad* GetWorldGeometry();

		static Block* GetBlock(glm::vec3 position);
		
		static World* Get();

		void UpdateWorldGeometry();
		
	protected:
		friend class Block;
		void AddBlock(glm::vec3 position, std::vector<TextureGeometry> texGeoms);

		Block* GetBlock(int x, int y, int z);
		void HideFace(GLuint index);
		void ShowFace(GLuint index, Instance face);

	private:
		static World* s_CurrentWorld;

		std::vector<std::vector<Chunk*>> m_Chunks;
		MultiQuad* m_WorldGeometry = Shape::Create<MultiQuad>();
	};
}
