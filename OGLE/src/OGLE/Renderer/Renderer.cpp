#include "oglepch.h"
#include "OGLE/Renderer/Renderer.h"

namespace OGLE {

	void Renderer::Draw()
	{
		GLCall(glDrawElements(GL_TRIANGLES, m_CurrentVAO->GetElementCount(), m_CurrentVAO->GetElementDataType(), nullptr));
	}

	void Renderer::SetClearColor(glm::vec4 clearColor = glm::vec4(0.1,0.1,0,1))
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void Renderer::Clear()
	{
		GLbitfield mask = 0;
		if (m_UseColorBuffer)
			mask = mask | GL_COLOR_BUFFER_BIT;
		if (m_UseDepthBuffer)
			mask = mask | GL_DEPTH_BUFFER_BIT;
		if (m_UseStencilBuffer)
			mask = mask | GL_STENCIL_BUFFER_BIT;
		GLCall(glClear(mask));
	}

	void Renderer::ChangeShaderProgram(ShaderProgram& shaderProgram)
	{
		DeactivateShaderProgram();
		InitShaderProgram(shaderProgram);
	}

	void Renderer::ChangeVAO(VertexArray& vao)
	{
		UnbindVAO();
		InitVAO(vao);
	}

	void Renderer::InitRenderer(ShaderProgram& shaderProgram, VertexArray& vao)
	{
		InitShaderProgram(shaderProgram); 
		InitVAO(vao);
		EnableColorBuffer(); 
		EnableDepthBuffer();
		SetClearColor();
	}

	void Renderer::InitShaderProgram(ShaderProgram& shaderProgam)
	{
		SetShaderProgram(shaderProgam);
		ActivateShaderProgram();
	}

	void Renderer::SetShaderProgram(ShaderProgram& shaderProgram)
	{
		m_CurrentShaderProgram = &shaderProgram;
	}

	void Renderer::ActivateShaderProgram()
	{
		m_CurrentShaderProgram->Activate();
	}

	void Renderer::DeactivateShaderProgram()
	{
		m_CurrentShaderProgram->Deactivate();
	}

	void Renderer::ClearShaderProgram()
	{
		m_CurrentShaderProgram = nullptr;
	}

	void Renderer::InitVAO(VertexArray& vao)
	{
		SetVAO(vao);
		BindVAO();
	}

	void Renderer::SetVAO(VertexArray& vao)
	{
		m_CurrentVAO = &vao;
	}

	void Renderer::BindVAO()
	{
		m_CurrentVAO->Bind();
	}

	void Renderer::UnbindVAO()
	{
		m_CurrentVAO->Unbind();
	}

	void Renderer::ClearVAO()
	{
		m_CurrentVAO = nullptr;
	}

}