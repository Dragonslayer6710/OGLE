#include "oglepch.h"

#include "OGLE/MineClone/Block.h"
#include "OGLE/MineClone/World.h"

namespace OGLE {

	int Block::hiddenFaces = 0;
	GLuint Block::numBlocks = 0;
	Block::Block(glm::vec3 position, GLushort id /*= 2*/)
		: m_Position(position), m_ModelTransform(NewModelMatrix(position)), m_BlockID(id)
	{
		m_FaceTexGeoms = GetBlockTextureMap(m_BlockID);
		World::Get()->AddBlock(m_Position, *m_FaceTexGeoms);
		auto it = World::Get()->GetWorldGeometry()->GetInstances()->GetElements()->begin();
		m_Faces = new std::vector<Instance>(it+m_WorldBlockID, it+m_WorldBlockID+6);
	}
	void Block::UpdateGeometry()
	{
		for (GLushort face = 0; face < 6; face++)
		{
			Ref<Block> adjacentBlock = nullptr;
			switch (face)
			{
			case BlockSouth:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x, m_Position.y, m_Position.z + 1));
				break;
			case BlockNorth:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x, m_Position.y, m_Position.z - 1));
				break;
			case BlockWest:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x - 1, m_Position.y, m_Position.z));
				break;
			case BlockEast:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x + 1, m_Position.y, m_Position.z));
				break;
			case BlockBottom:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x, m_Position.y - 1, m_Position.z));
				break;
			case BlockTop:
				adjacentBlock = World::Get()->GetBlock(glm::vec3(m_Position.x, m_Position.y + 1, m_Position.z));
				break;
			}

			if (adjacentBlock != nullptr)
				if (adjacentBlock->GetBlockID() != -1)
					if (m_VisibleFaces[face])
					{
						HideFace(face);
						hiddenFaces+=1;
						continue;
					}
			if (!m_VisibleFaces[face])
				ShowFace(face);
		}
	}

	void Block::HideFace(GLushort face)
	{
		m_VisibleFaces[face] = false;
		//OGLE_CORE_INFO("Block {0}: Culling Face: {1} FaceID: {2}", m_WorldBlockID, face, m_WorldBlockID*6 + face);
		World::Get()->HideFace(m_WorldBlockID*6 + face);
	}

	void Block::ShowFace(GLushort face)
	{
		m_VisibleFaces[face] = true;
		World::Get()->ShowFace(m_WorldBlockID + face, (*m_Faces)[face]);
	}

	GLushort Block::GetBlockID()
	{
		return m_BlockID;
	}

	GLuint Block::GetWorldBlockID()
	{
		return m_WorldBlockID;
	}

}
