#include "oglepch.h"
#include "OGLE/Display/Renderer/Shader.h"

namespace OGLE {
	ShaderProgram* ShaderProgram::s_ActiveShaderProgram;

	// Create new shader object and get its ID
	Shader::Shader(GLenum shaderType, std::string shaderFile)
		: m_ShaderType(shaderType)
	{
		GLCall(m_ShaderID = glCreateShader(shaderType));
		if (s_ParsedShaders.find(m_ShaderType) != s_ParsedShaders.end())
			s_ParsedShaders[m_ShaderType] = std::unordered_map<std::string, std::string>();

		// Parse Shader File source code
		if (s_ParsedShaders[m_ShaderType].find(shaderFile) == s_ParsedShaders[m_ShaderType].end())
			ParseShaderFile(shaderFile);
	
		const char* source = s_ParsedShaders[m_ShaderType][shaderFile].c_str();

	    // Provide the source code to the shader
		GLCall(glShaderSource(m_ShaderID, 1, &source, NULL));
		GLCall(glCompileShader(m_ShaderID));

		GLCall(glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &m_CompileStatus));
		GLCall(glGetShaderInfoLog(m_ShaderID, 1024, &m_LogLength, m_LogMessage));

	}

	// Deletes the shader referenced by m_ShaderID
	Shader::~Shader()
	{
		GLCall(glDeleteShader(m_ShaderID));
	}

	// Check to see if this file has been loaded before, otherwise parse it and store to cache
	void Shader::ParseShaderFile(const std::string shaderFile) const
	{
		std::ifstream in(cwd + "\\assets\\shaders\\" + shaderFile);
		std::string result((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		s_ParsedShaders[m_ShaderType][shaderFile] = result.c_str();
	}


	// Create Program object and refer to it using m_ProgramID
	ShaderProgram::ShaderProgram(std::string shaderList[s_TotalShaderTypes])
	{
		GLCall(m_ProgramID = glCreateProgram());
		//PrintInitialized();
		m_ShaderCollection = new ShaderCollection(shaderList);
		for (auto& kv : m_ShaderCollection->compiledShaders) {
			Shader* shader = kv.second;
			if ((*shader).GetCompileStatus() == GL_FALSE) 
			{
				OGLE_CORE_ERROR((*shader).GetLogMessage());
				OGLE_CORE_ASSERT(false);
			}
			else {
				GLCall(glAttachShader(m_ProgramID, (*shader).GetID()));
			}
		}

		GLCall(glLinkProgram(m_ProgramID));
		GLCall(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &m_LinkStatus));
		GLCall(glGetProgramInfoLog(m_ProgramID, 1024, &m_LogLength, m_LogMessage));

		if (m_LinkStatus == GL_FALSE)
		{
			OGLE_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_LogMessage);
			GLCall(glDeleteProgram(m_ProgramID));
		}
		else {
			for (auto& kv : m_ShaderCollection->compiledShaders) {
				Shader* shader = kv.second;
				delete shader;
			}
		}
		
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ProgramID);
	}

	void ShaderProgram::Activate()
	{
		if (m_IsActive)
			return;
		if (s_ActiveShaderProgram != nullptr)
			if (s_ActiveShaderProgram != this)
				s_ActiveShaderProgram->Deactivate();
		s_ActiveShaderProgram = this;
		GLCall(glUseProgram(m_ProgramID));
		m_IsActive = true;
		//PrintActivationStatus();
	}

	void ShaderProgram::Deactivate()
	{
		if (!m_IsActive)
			return;
		GLCall(glUseProgram(0));
		m_IsActive = false;
		//PrintActivationStatus();
	}

	void ShaderProgram::SetUniform1i(const std::string& uName, GLint value)
	{
		glUniform1i(GetUniformLocation(uName), value);
	}

	void ShaderProgram::SetUniform2fv(const std::string& uName, glm::vec2 value)
	{
		//GLCall(glUniform2fv(GetUniformLocation(uName), 1, glm::value_ptr(value)));
		GLCall(glUniform2f(GetUniformLocation(uName), value.x, value.y));
	}

	void ShaderProgram::SetUniform3fv(const std::string& uName, glm::vec3 value)
	{
		GLCall(glUniform3fv(GetUniformLocation(uName), 1, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniform4fv(const std::string& uName, glm::vec4 value)
	{
		GLCall(glUniform4fv(GetUniformLocation(uName), 1, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniformMatrix4fv(const std::string& uName, glm::mat4 value)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(uName), 1, GL_FALSE, glm::value_ptr(value)));
	}

	GLuint ShaderProgram::GetUniformLocation(const std::string& uName)
	{
		if (m_CachedUniformLocations.find(uName.c_str()) != m_CachedUniformLocations.end())
			return m_CachedUniformLocations[uName.c_str()];
		GLCall(m_CachedUniformLocations[uName] = glGetUniformLocation(m_ProgramID, uName.c_str()));
		return m_CachedUniformLocations[uName];

	}

}