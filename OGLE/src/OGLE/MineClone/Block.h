#pragma once

#include "OGLE/Maths/Geometry/Geometry3D.h"

namespace OGLE {
	class World;

	static enum BlockSide {
		BlockSouth,
		BlockNorth,
		BlockWest,
		BlockEast,
		BlockBottom,
		BlockTop
	};

	class Chunk;
	class World;

	class Block
	{
	public:
		static Ref<Block> Create(glm::vec3 position, GLushort id = 2)
		{
			return CreateRef<Block>(position, id);
		}

		void Load(std::vector<Ref<Instance>>& blockAlloc);
		void Unload();

		Block(glm::vec3 position, GLushort id = 2);

		void UpdateGeometry();

		void HideFace(int face);

		void ShowFace(int face);

		glm::vec3 GetPos() { return m_Position; }

		GLushort GetBlockID();

		GLuint Block::GetBlockInstanceID();

		static void ResetBlocks() {
			numBlocks = 0;
		}

		static Ref<TextureAtlas> s_TextureAtlas;

	private:
		glm::vec3 m_Position;
		glm::mat4 m_ModelTransform;
		GLushort m_BlockID;
		GLuint m_BlockInstanceID = numBlocks++;

		std::array<Instance, 6> m_Faces;

		std::array<Ref<Instance>, 6> m_LoadedFaces;
		std::array<Instance, 6> m_HiddenFaces;


		static GLuint numBlocks;

		static std::vector<TextureGeometry> MapTexture(GLushort blockID);
		void MapTexture();
	};
}
