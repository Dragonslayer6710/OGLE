#include "oglepch.h"
#include "OGLE/Renderer/Renderer.h"

namespace OGLE {

	Renderer::Renderer(GLsizei width, GLsizei height)
	{
		InitRenderer(width, height);
	}

	Renderer::Renderer(GLsizei width, GLsizei height, ShaderProgram& shaderProgram, VertexArray& vao)
	{
		InitRenderer(width, height);
		InitShaderProgram(shaderProgram);
		InitVAO(vao);
	}

	void Renderer::SetViewPort(GLint left, GLint bottom, GLsizei width, GLsizei height)
	{
		GLCall(glViewport(left, bottom, width, height));
	}

	void Renderer::OnWindowResize(GLsizei newWidth, GLsizei newHeight)
	{
		m_Width = newWidth;
		m_Height = newHeight;
		m_AspectRatio = m_Width / m_Height;
		SetViewPort(m_Left, m_Bottom, m_Width, m_Height);
	}

	void Renderer::Draw()
	{
		GLCall(glDrawElements(GL_TRIANGLES, m_CurrentVAO->GetElementCount(), m_CurrentVAO->GetElementDataType(), nullptr));
	}

	void Renderer::SetClearColor(glm::vec4 clearColor = glm::vec4(0.1, 0.1, 0, 1))
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

	void Renderer::InitRenderer(GLsizei width, GLsizei height)
	{
		OnWindowResize(width, height);
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
		if (!(m_CurrentShaderProgram == nullptr))
			m_CurrentShaderProgram->Activate();
	}

	void Renderer::DeactivateShaderProgram()
	{
		if (!(m_CurrentShaderProgram == nullptr))
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
		if (!(m_CurrentVAO == nullptr))
			m_CurrentVAO->Bind();
	}

	void Renderer::UnbindVAO()
	{
		if (!(m_CurrentVAO == nullptr))
			m_CurrentVAO->Unbind();
	}

	void Renderer::ClearVAO()
	{
		m_CurrentVAO = nullptr;
	}

}