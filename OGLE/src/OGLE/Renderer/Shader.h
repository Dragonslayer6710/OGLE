#pragma once
#include "OGLE/Renderer/VertexArray.h"

namespace OGLE {

	inline std::unordered_map<GLenum,std::unordered_map<std::string, std::string>> s_ParsedShaders;

	class Shader 
	{
	public:
		Shader(GLenum shaderType, const std::string shaderFile);
		Shader() {};
		~Shader();

		GLuint GetID() const { return m_ShaderID; }


		GLint GetCompileStatus() const { return m_CompileStatus; }
		GLsizei GetLogLength() const { return m_LogLength; }
		const GLchar* GetLogMessage() { return m_LogMessage; }

	protected:
		void ParseShaderFile(const std::string shaderFile) const;

	private:
		GLuint m_ShaderID;
		GLenum m_ShaderType;

		GLint m_CompileStatus;
		GLsizei m_LogLength = 0;
		GLchar m_LogMessage[1024];
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader(const std::string shaderName)
			:Shader(GL_VERTEX_SHADER, shaderName + ".vert") {}
	};

	class FragmentShader : public Shader
	{
	public:
		FragmentShader(const std::string shaderName)
			:Shader(GL_FRAGMENT_SHADER, shaderName + ".frag") {}
	};

	
	static const GLuint s_ShaderTypes[] =
	{
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};
	static const unsigned int s_TotalShaderTypes = 2;
	struct ShaderCollection {
		std::unordered_map<GLenum, std::string> usedShaders =
		{
			{GL_VERTEX_SHADER, "default"},
			{GL_FRAGMENT_SHADER, "default"}
		};
		std::unordered_map<GLenum, Shader*> compiledShaders =
		{
			{GL_VERTEX_SHADER, new Shader()},
			{GL_FRAGMENT_SHADER, new Shader()}
		};
		ShaderCollection(std::string shaderList[s_TotalShaderTypes] = NULL) {
			if (shaderList)
				for (int i = 0; i < s_TotalShaderTypes; i++)
					usedShaders[s_ShaderTypes[i]] = shaderList[i];
			InitShaders();
		}

		void InitShaders() {
			Shader* shader;
			for (auto& kv : usedShaders) {
				switch (kv.first) {
				case GL_VERTEX_SHADER:
					shader =  new VertexShader(kv.second);
					break;
				case GL_FRAGMENT_SHADER:
					shader = new FragmentShader(kv.second);
					break;
				default:
					continue;
				};
				compiledShaders[kv.first] = shader;
			}
		}
		
	};

	class ShaderProgram
	{
	public:
		ShaderProgram(std::string shaderList[s_TotalShaderTypes] = NULL);
		~ShaderProgram();

		void Activate();
		void Deactivate();

		void PrintStatus(const char* status) { std::cout << "Shader Program (ID " << m_ProgramID << "): " << status << std::endl; }
		void PrintInitialized() { PrintStatus("Initialized"); }
		void PrintActivationStatus() { PrintStatus((m_IsActive) ? "Activated" : "Deactivated"); }

		void SetUniform2f(const std::string& uName, glm::vec2 value);
		void SetUniform3f(const std::string& uName, glm::vec3 value);
		void SetUniform4f(const std::string& uName, glm::vec4 value);

	private:
		GLuint GetUniformLocation(const std::string& uName);
	private:
		GLuint m_ProgramID;
		ShaderCollection* m_ShaderCollection;
		std::unordered_map<std::string, GLuint> m_CachedUniformLocations;

		GLint m_LinkStatus;
		GLsizei m_LogLength = 0;
		GLchar m_LogMessage[1024];

		bool m_IsActive = false;
	};
}