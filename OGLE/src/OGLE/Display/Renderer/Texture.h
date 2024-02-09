#pragma once
#include "OGLE/OGL/OpenGL.h"
#include "OGLE/Buffer/Data/Data.h"
#include <map>"
namespace OGLE{

	class Texture
	{
	public:
		Texture(std::string textureFile);
		~Texture();

		void Bind();
		void Unbind();

		GLuint GetTextureID();
		GLuint GetTextureSlot();

		GLsizei GetWidth();
		GLsizei GetHeight();

	protected:
		static void SetParameterI(GLenum target, GLenum param, GLint value);

	private:

		void ClearTextureSlot();

		static GLuint GetNextTextureSlot();

		

	protected:
		glm::vec2 m_Size;

	private:
		GLuint m_TextureID;
		GLuint m_TextureSlot;

		bool m_IsBound =false;
		static std::map<GLuint, bool> s_TextureSlots;
		static std::vector<GLuint> s_FreedTextureSlots;
	};

	class TextureAtlas : public Texture
	{
	public:
		TextureGeometry GetSubTexture(GLuint id);

	protected:
		TextureAtlas(std::string textureFile);
		void AddSubTexture(glm::vec2 position, glm::vec2 size);

	private:
		std::vector<TextureGeometry> m_SubTextures;
	};

	class UniformTextureAtlas : public TextureAtlas
	{
	public:
		UniformTextureAtlas(std::string textureFile, glm::vec2 subTexSize);
	};
}