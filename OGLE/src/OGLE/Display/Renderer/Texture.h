#pragma once
#include "OGLE/OGL/OpenGL.h"
#include "OGLE/Buffer/Data/Data.h"
#include <map>"
namespace OGLE{

	class Texture
	{
	public:
		template<typename T, typename ... Args>
		constexpr Ref<T> Create(Args&& ... args)
		{
			return CreateRef<T>(std::forward<Args>(args)...);
		}

		Texture(std::string textureFile);
		~Texture();

		bool IsAtlas();

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
		bool m_IsAtlas = false;
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
		static Ref<UniformTextureAtlas> Create(std::string textureFile, glm::vec2 subTexSize)
		{
			return CreateRef<UniformTextureAtlas>(textureFile, subTexSize);
		}

		UniformTextureAtlas(std::string textureFile, glm::vec2 subTexSize);
	};
}