#include "oglepch.h"
#include "OGLE/Display/Renderer/Texture.h"
#include <stb_image.h>
namespace OGLE {
	
	std::map<GLuint, bool> Texture::s_TextureSlots;
	std::vector<GLuint> Texture::s_FreedTextureSlots;

	Texture::Texture(std::string textureFile)
	{
		InitTexture(textureFile);
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TextureID));
	}

	void Texture::Bind()
	{
		if (m_IsBound)
			return;
		GetNextTextureSlot();
		GLCall(glActiveTexture(m_TextureSlot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
		m_IsBound = true;
	}

	void Texture::Unbind()
	{
		if (!m_IsBound)
			return;
		ClearTextureSlot();
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_IsBound = false;
	}

	GLuint Texture::GetTextureID()
	{
		return m_TextureID;
	}

	GLuint Texture::GetTextureSlot()
	{
		return m_TextureID;
	}

	void Texture::SetParameterI(GLenum target, GLenum param, GLint value)
	{
		GLCall(glTexParameteri(target, param, value));
	}

	void Texture::InitTexture(std::string textureFile)
	{
		GLint width, height, numColCh;
		GLubyte* bytes = stbi_load((cwd+"\\assets\\textures\\" + textureFile).c_str(), &width, &(int&)height, &numColCh, 0);
		m_Size = glm::vec2(width, height);
		GLCall(glGenTextures(1, &m_TextureID));
		Bind();

		SetParameterI(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		SetParameterI(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		SetParameterI(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		SetParameterI(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(bytes);
		Unbind();
	}


	void Texture::SetTextureSlot()
	{
		m_TextureSlot = GetNextTextureSlot();
	}

	void Texture::ClearTextureSlot()
	{
		ClearTextureSlot(m_TextureSlot);
		m_TextureSlot = NULL;
	}

	GLuint Texture::GetNextTextureSlot()
	{
		GLuint textureSlot;
		if (s_FreedTextureSlots.empty())
		{
			textureSlot = GL_TEXTURE0 + s_TextureSlots.size();
		}
		else {
			textureSlot = s_FreedTextureSlots.back();
			s_FreedTextureSlots.pop_back();
		}
		s_TextureSlots[textureSlot] = true;
		return textureSlot;
	}

	void Texture::ClearTextureSlot(GLuint textureSlot)
	{
		s_TextureSlots[textureSlot] = false;
		int lastElem = s_FreedTextureSlots.size() - 1;
		for (int i = 0; i <= lastElem; i++)
		{
			if (i == lastElem)
				s_FreedTextureSlots.push_back(textureSlot);
			else if (s_FreedTextureSlots[i] > textureSlot)
				s_FreedTextureSlots.insert(s_FreedTextureSlots.begin() + i + 1, textureSlot);
		}

	}

	TextureAtlas::TextureAtlas(std::string textureFile) :Texture(textureFile)
	{

	}

	void TextureAtlas::AddSubTexture(SubTexture subTexture)
	{
		m_SubTextures.push_back(subTexture);
	}

	void TextureAtlas::AddSubTexture(GLuint left, GLuint top, GLsizei width, GLsizei height)
	{
		AddSubTexture(CreateSubTexture(left, top, width, height));
	}

	SubTexture TextureAtlas::GetSubTexture(GLuint id)
	{
		return m_SubTextures[id];
	}

	SubTexture TextureAtlas::CreateSubTexture(GLuint left, GLuint top, GLsizei width, GLsizei height)
	{
		OGLE_CORE_ASSERT
		(
			!(left < 0 || left >= m_Size.x || top < 0 || top >= m_Size.y || left + width < 0 || left + width >= m_Size.x || top + height < 0 || top + height >= m_Size.y),
			"TEXTURE ERROR: Dimensions given for SubTexture exceed the dimensions of the the full texture"
		);
		return SubTexture(glm::vec2(left, top), glm::vec2(width, height), m_Size);
	}

	UniformTextureAtlas::UniformTextureAtlas(std::string textureFile, GLsizei subWidth, GLsizei subHeight) : TextureAtlas(textureFile), m_SubSize(subWidth, subHeight), m_MaxRightBottom((m_Size / m_SubSize))
	{
		glm::vec2 floor = glm::floor(m_MaxRightBottom);
		// Check if MaxRightBottom are integers
		OGLE_CORE_ASSERT
		(
			 !(floor.x!= m_MaxRightBottom.x || floor.y != m_MaxRightBottom.y),
			std::string("TEXTURE ERROR: SubTexture size {0}x{1} does not divide the texture into uniform sections", subWidth, subHeight).c_str()
		);

		for (int y = 0; y < m_MaxRightBottom.y; y++)
			for (int x = 0; x < m_MaxRightBottom.x; x++) {
				AddSubTexture(x, y);
			}
	}

	glm::vec2 UniformTextureAtlas::GetSubSize()
	{
		return m_SubSize;
	}


	void UniformTextureAtlas::AddSubTexture(GLuint left, GLuint top)
	{
		TextureAtlas::AddSubTexture(left, top, m_SubSize.x, m_SubSize.y);
	}

}