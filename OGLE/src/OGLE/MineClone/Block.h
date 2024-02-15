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

		static Ref<TextureAtlas> s_TextureAtlas;

	private:
		glm::vec3 m_Position;
		glm::mat4 m_ModelTransform;
		GLushort m_BlockID;
		GLuint m_WorldBlockID = numBlocks++;
		std::vector<TextureGeometry>* m_FaceTexGeoms;

		std::vector<Instance>* m_Faces;
		bool m_VisibleFaces[6];

		static GLuint numBlocks;

		static std::vector<TextureGeometry>* MapTexture(GLushort blockID);
	};
}
