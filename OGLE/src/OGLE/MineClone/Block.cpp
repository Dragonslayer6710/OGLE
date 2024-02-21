#include "oglepch.h"

#include "OGLE/MineClone/Block.h"
#include "OGLE/MineClone/World.h"

namespace OGLE {

	GLuint Block::numBlocks = 0;

	OGLE::Ref<TextureAtlas> Block::s_TextureAtlas;

	std::vector<TextureGeometry> Block::MapTexture(GLushort blockID)
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
			return std::vector<TextureGeometry>
			{
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry(),
				TextureGeometry()
			};
		}
		std::vector<TextureGeometry> m_SideTexGeoms = std::vector<TextureGeometry>();
		for (int side = 0; side < 6; side++)
			m_SideTexGeoms.push_back(s_TextureAtlas->GetSubTexture(subTexIDs[side]));
		return m_SideTexGeoms;
	}

	void Block::MapTexture()
	{
		int cnt = 0;
		std::vector<TextureGeometry> texGeoms = MapTexture(m_BlockID);
		for (TextureGeometry& texGeom : texGeoms)
			m_Faces[cnt++].TexGeometry = texGeom;
	}

	Block::Block(glm::vec3 position, GLushort id)
		: m_Position(position),
		m_ModelTransform(NewModelMatrix(position)),
		m_BlockID(id), m_Faces(NewQuadCuboid(position))
	{
		if (m_BlockID == GLushort(-1))
			for (GLushort face = 0; face < 6; face++)
				HideFace(face);
		else
			MapTexture();
	}

	void Block::Load(std::vector<Ref<Instance>>& blockAlloc)
	{
		for (int i = 0; i < 6; i++) {
			// Update blockAlloc with pointers to newly created instances
			m_LoadedFaces[i] = blockAlloc[i];
			*m_LoadedFaces[i] = m_Faces[i];
		}
	}

	void Block::Unload()
	{
		for (int i = 0; i < 6; i++)
			m_LoadedFaces[i] = nullptr;
	}


	void Block::UpdateGeometry()
	{
		if (m_BlockID == GLushort(-1))
			return;
		for (int face = 0; face < 6; face++)
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

			if (m_HiddenFaces[face].IsNull())
				if (adjacentBlock != nullptr)
					if (adjacentBlock->GetBlockID() != GLushort(-1))
					{
						HideFace(face);
						continue;
					}
			if (!m_HiddenFaces[face].IsNull())
				ShowFace(face);
		}
	}

	void Block::HideFace(int face)
	{
		m_HiddenFaces[face] = m_Faces[face];
		m_Faces[face] = Instance();
	}

	void Block::ShowFace(int face)
	{
		m_Faces[face] = m_HiddenFaces[face];
		m_HiddenFaces[face] = Instance();
	}

	GLushort Block::GetBlockID()
	{
		return m_BlockID;
	}

	GLuint Block::GetBlockInstanceID()
	{
		return m_BlockInstanceID;
	}

}
