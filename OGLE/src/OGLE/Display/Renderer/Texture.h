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

		GLsizei GetWidth() { return m_Size.x; }
		GLsizei GetHeight() { return m_Size.y; }
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
		{
			Size = subSize;
			Position = subPos;
			//Position.y = 1.0f - Position.y;
		}
	};


	class TextureAtlas : public Texture
	{
	public:
		SubTexture GetSubTexture(GLuint id);

	protected:
		TextureAtlas(std::string textureFile);
		
	protected:
		void AddSubTexture(GLfloat left, GLfloat top, GLfloat width, GLfloat height);
		void AddSubTexture(SubTexture subTexture);

	private:
		SubTexture CreateSubTexture(GLfloat left, GLfloat top, GLfloat width, GLfloat height);

	private:
		std::vector<SubTexture> m_SubTextures;
	};

	class UniformTextureAtlas : public TextureAtlas
	{
	public:
		UniformTextureAtlas(std::string textureFile, GLsizei subWidth, GLsizei subHeight);
		glm::vec2 GetSubSize();
		glm::vec2 GetUniformAtlasDims();
	protected:
		void AddSubTexture(GLfloat left, GLfloat top);
	private:
		glm::vec2 m_SubSize;
		glm::vec2 m_UniformAtlasDims;
	};
}