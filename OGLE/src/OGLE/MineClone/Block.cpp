#include "oglepch.h"

#include "OGLE/MineClone/Block.h"
#include "OGLE/MineClone/World.h"

namespace OGLE {

	int Block::hiddenFaces = 0;
	GLuint Block::numBlocks = 0;

	OGLE::Ref<OGLE::TextureAtlas> Block::s_TextureAtlas;

	std::vector<OGLE::TextureGeometry>* Block::MapTexture(GLushort blockID)
	{
		GLushort* subTexIDs;

		switch (blockID)
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
			};
		}
		std::vector<TextureGeometry>* m_SideTexGeoms = new std::vector<TextureGeometry>();
		for (int side = 0; side < 6; side++)
			m_SideTexGeoms->push_back(s_TextureAtlas->GetSubTexture(subTexIDs[side]));
		return m_SideTexGeoms;
	}

	Block::Block(glm::vec3 position, GLushort id /*= 2*/)
		: m_Position(position), m_ModelTransform(NewModelMatrix(position)), m_BlockID(id)
	{
		m_FaceTexGeoms = MapTexture(m_BlockID);
		auto it = World::Get()->AddBlock(m_Position, *m_FaceTexGeoms);
		m_Faces = new std::vector<Instance>(it+m_WorldBlockID, it+m_WorldBlockID+6);
		if (m_BlockID == GLushort(-1))
			for (GLushort face = 0; face < 6; face++)
				HideFace(face);
	}
	void Block::UpdateGeometry()
	{
		if (m_BlockID == GLushort(-1))
			return;
		for (GLushort face = 0; face < 6; face++)
		{
			Ref<Block> adjacentBlock = nullptr;
			glm::vec3 adjPos;
			switch (face)
			{
			case BlockSouth:
				adjPos = glm::vec3(m_Position.x, m_Position.y, m_Position.z + 1);
				break;
			case BlockNorth:
				adjPos = glm::vec3(m_Position.x, m_Position.y, m_Position.z - 1);
				break;
			case BlockWest:
				adjPos = glm::vec3(m_Position.x - 1, m_Position.y, m_Position.z);
				break;
			case BlockEast:
				adjPos = glm::vec3(m_Position.x + 1, m_Position.y, m_Position.z);
				break;
			case BlockBottom:
				adjPos = glm::vec3(m_Position.x, m_Position.y - 1, m_Position.z);
				break;
			case BlockTop:
				adjPos = glm::vec3(m_Position.x, m_Position.y + 1, m_Position.z);
				break;
			};

			adjacentBlock = World::Get()->GetBlock(adjPos);	
			if (adjacentBlock != nullptr)
				if (adjPos != adjacentBlock->GetPos())
				OGLE_CORE_INFO("{0} vs {1}", adjPos, adjacentBlock->GetPos());

			if (m_VisibleFaces[face])
				if (adjacentBlock != nullptr)
					if (adjacentBlock->GetBlockTypeID() != GLushort(-1))

					{
						HideFace(face);
						hiddenFaces += 1;
						continue;
					}
			if (!m_VisibleFaces[face])
				ShowFace(face);
		}
	}

	void Block::HideFace(GLushort face)
	{
		m_VisibleFaces[face] = false;
		World::Get()->HideFace(m_WorldBlockID*6 + face);
	}

	void Block::ShowFace(GLushort face)
	{
		m_VisibleFaces[face] = true;
		World::Get()->ShowFace(m_WorldBlockID + face, (*m_Faces)[face]);
	}

	GLushort Block::GetBlockTypeID()
	{
		return m_BlockID;
	}

	GLuint Block::GetWorldBlockID()
	{
		return m_WorldBlockID;
	}

}
