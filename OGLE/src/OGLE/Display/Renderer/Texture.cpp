#include "oglepch.h"
#include "OGLE/Display/Renderer/Texture.h"
#include <stb_image.h>
namespace OGLE {
	
	std::map<GLuint, bool> Texture::s_TextureSlots;
	std::vector<GLuint> Texture::s_FreedTextureSlots;

	Texture::Texture(std::string textureFile)
	{
		GLint width, height, numColCh;
		GLubyte* bytes = stbi_load((cwd + "\\assets\\textures\\" + textureFile).c_str(), &width, &(int&)height, &numColCh, 0);
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

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TextureID));
	}

	bool Texture::IsAtlas()
	{
		return m_IsAtlas;
	}

	void Texture::Bind()
	{
		if (m_IsBound)
			return;
		m_TextureSlot = GetNextTextureSlot();
		GLCall(glActiveTexture(GL_TEXTURE0 + m_TextureSlot));
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
		return m_TextureSlot;
	}

	GLsizei Texture::GetWidth()
	{
		return m_Size.x;
	}

	GLsizei Texture::GetHeight()
	{
		return m_Size.y;
	}

	void Texture::SetParameterI(GLenum target, GLenum param, GLint value)
	{
		GLCall(glTexParameteri(target, param, value));
	}

	void Texture::ClearTextureSlot()
	{
		s_TextureSlots[m_TextureSlot] = false;
		int lastElem = s_FreedTextureSlots.size() - 1;
		for (int i = 0; i <= lastElem; i++)
		{
			if (i == lastElem)
				s_FreedTextureSlots.push_back(m_TextureSlot);
			else if (s_FreedTextureSlots[i] > m_TextureSlot) {
				s_FreedTextureSlots.insert(s_FreedTextureSlots.begin() + i + 1, m_TextureSlot);
				break;
			}
		}
		m_TextureSlot = NULL;
	}

	GLuint Texture::GetNextTextureSlot()
	{
		GLuint textureSlot;
		if (s_FreedTextureSlots.empty())
		{
			textureSlot = s_TextureSlots.size();
		}
		else {
			textureSlot = s_FreedTextureSlots.back();
			s_FreedTextureSlots.pop_back();
		}
		s_TextureSlots[textureSlot] = true;
		return textureSlot;
	}

	TextureAtlas::TextureAtlas(std::string textureFile)
		: Texture(textureFile)
	{

	}

	void TextureAtlas::AddSubTexture(glm::vec2 position, glm::vec2 size)
	{
		m_SubTextures.push_back(TextureGeometry(position, size));
	}

	TextureGeometry TextureAtlas::GetSubTexture(GLuint id)
	{
		return m_SubTextures[id];
	}


	UniformTextureAtlas::UniformTextureAtlas(std::string textureFile, glm::vec2 subTexSize)
		: TextureAtlas(textureFile)
	{
		glm::vec2 RelSize = subTexSize / m_Size;
		glm::vec2 AtlasDims = m_Size / subTexSize;
		glm::vec2 floor = glm::floor(AtlasDims);

		// Check if MaxRightBottom are integers
		OGLE_CORE_ASSERT
		(
			 !(floor.x!= AtlasDims.x || floor.y != AtlasDims.y),
			std::string("TEXTURE ERROR: SubTexture size {0}x{1} does not divide the texture into uniform sections", subTexSize.x, subTexSize.y).c_str()
		);

		for (int y = 0; y < AtlasDims.y; y++)
			for (int x = 0; x < AtlasDims.x; x++) {
				AddSubTexture(RelSize * glm::vec2(x,AtlasDims.y-1-y), RelSize);
			}
	}

}