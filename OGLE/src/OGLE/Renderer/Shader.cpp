#include "oglepch.h"
#include "OGLE/Renderer/Shader.h"

namespace OGLE {

	// Create new shader object and get its ID
	Shader::Shader(GLenum shaderType, std::string shaderFile)
		: m_ShaderID(glCreateShader(shaderType)), m_ShaderType(shaderType)
	{
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
		std::ifstream in("C:\\Users\\harri\\source\\repos\\OGLE\\OGLE\\assets\\shaders\\" + shaderFile);
		std::string result((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		s_ParsedShaders[m_ShaderType][shaderFile] = result.c_str();
	}


	// Create Program object and refer to it using m_ProgramID
	ShaderProgram::ShaderProgram(std::string shaderList[s_TotalShaderTypes])
		: m_ProgramID(glCreateProgram())
	{
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
		
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ProgramID);
	}

	void ShaderProgram::Activate()
	{
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::Deactivate()
	{
		glUseProgram(0);
	}

}