#pragma once
#include "OGLE/OGL/OpenGL.h"
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
		void SetParameterI(GLenum target, GLenum param, GLint value);


	private:
		void InitTexture(std::string textureFile);

		void SetTextureSlot();
		void ClearTextureSlot();

		static GLuint GetNextTextureSlot();
		static void ClearTextureSlot(GLuint textureSlot);

		

	protected:
		glm::vec2 m_Size;

	private:
		GLuint m_TextureID;
		GLuint m_TextureSlot;

		bool m_IsBound;
		static std::map<GLuint, bool> s_TextureSlots;
		static std::vector<GLuint> s_FreedTextureSlots;
	};

	struct SubTexture {
		glm::vec2 Position;
		glm::vec2 Size;

		SubTexture(glm::vec2 subPos, glm::vec2 subSize)
			: Position(subPos), Size(subSize)
		{}
	};


	class TextureAtlas : public Texture
	{
	public:
		SubTexture GetSubTexture(GLuint id);

	protected:
		TextureAtlas(std::string textureFile);
		void AddSubTexture(glm::vec2 position, glm::vec2 size);

	private:
		std::vector<SubTexture> m_SubTextures;
	};

	class UniformTextureAtlas : public TextureAtlas
	{
	public:
		UniformTextureAtlas(std::string textureFile, glm::vec2 subTexSize);
	};
}