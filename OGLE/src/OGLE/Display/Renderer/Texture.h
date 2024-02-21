#pragma once
#include "OGLE/OGL/OpenGL.h"
#include "OGLE/Buffer/Data/Data.h"
#include <map>"
namespace OGLE{

	class Texture
	{
	public:
		// Define the equality operator
		bool operator==(const Texture& other) const {
			return m_TextureID == other.m_TextureID;
		}

		// Define the equality operator
		bool operator!=(const Texture& other) const {
			return !(m_TextureID == other.m_TextureID);
		}

		static Scope<Texture> Create(const Texture& other) {
			return CreateScope<Texture>(other);
		}

		Ref<Texture> Create(std::string textureFile)
		{
			return CreateRef<Texture>(textureFile);
		}

		Texture() = default;

		Texture(std::string textureFile);
		// Copy constructor
		Texture(const Texture& other)
			: m_IsAtlas(other.m_IsAtlas), m_Size(other.m_Size), m_TextureID(other.m_TextureID), m_TextureSlot(other.m_TextureSlot), m_IsBound(other.m_IsBound) {
			// If any member requires deep copying, perform it here
		}
		~Texture();

		bool IsAtlas();

		void Bind();
		void Unbind();

		GLuint GetTextureID();
		GLuint GetTextureSlot();

		GLsizei GetWidth();
		GLsizei GetHeight();

	protected:
		static Texture s_BoundTexture;
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
		Ref<Texture> Create(std::string textureFile) = delete;
		static Ref<UniformTextureAtlas> Create(std::string textureFile, glm::vec2 subTexSize)
		{
			return CreateRef<UniformTextureAtlas>(textureFile, subTexSize);
		}

		UniformTextureAtlas(std::string textureFile, glm::vec2 subTexSize);
	};
}