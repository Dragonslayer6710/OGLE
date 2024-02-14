#pragma once

#include "OGLE/Maths/Geometry/Geometry3D.h"

namespace OGLE {
	class World;

	static std::vector<TextureGeometry>* BlockTextureMap(TextureAtlas* textureAtlas, GLushort subTextureIDs[6])
	{
		std::vector<TextureGeometry>* m_SideTexGeoms = new std::vector<TextureGeometry>();
		for (int side = 0; side < 6; side++)
			m_SideTexGeoms->push_back(textureAtlas->GetSubTexture(subTextureIDs[side]));
		return m_SideTexGeoms;
	}

	inline UniformTextureAtlas* s_TextureAtlas = nullptr;

	static std::vector<TextureGeometry>* GetBlockTextureMap(GLushort id)
	{
		GLushort* subTexIDs;

		switch (id)
		{			
		case 0:
			subTexIDs = new GLushort[6]{ 3, 3, 3, 3, 2, 0 };
			break;
		case 1:
			subTexIDs = new GLushort[6]{ 1, 1, 1, 1, 1, 1 };
			break;
		case 2:
			subTexIDs = new GLushort[6]{ 2, 2, 2, 2, 2, 2 };
			break;
		case 3:
			subTexIDs = new GLushort[6]{ 7, 7, 7, 7, 7, 7 };
			break;
		default:
			return new std::vector<TextureGeometry>
			{
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry()
			};;
		}
		return BlockTextureMap(s_TextureAtlas, subTexIDs);
	}

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
		Block(glm::vec3 position, GLushort id = 2);

		void UpdateGeometry();

		void HideFace(GLushort face);

		void ShowFace(GLushort face);

		glm::vec3 GetPos() { return m_Position; }

		GLushort GetBlockTypeID();

		GLuint Block::GetWorldBlockID();
		static int hiddenFaces;

		static void ResetBlocks() {
			numBlocks = 0;
		}
	private:
		glm::vec3 m_Position;
		glm::mat4 m_ModelTransform;
		GLushort m_BlockID;
		GLuint m_WorldBlockID = numBlocks++;
		std::vector<TextureGeometry>* m_FaceTexGeoms;

		std::vector<Instance>* m_Faces;
		bool m_VisibleFaces[6];

		static GLuint numBlocks;
	};
}
