#include "oglepch.h"
#include "OGLE/Display/Renderer/Renderer.h"

namespace OGLE {


	Renderer::Renderer(GLsizei width, GLsizei height, GLfloat fovDeg/*=DefFOVDegrees*/, GLfloat nearPlane/*=DefNearPlane*/, GLfloat farPlane/*=DefFarPlane*/)
	{
		InitRenderer(width, height, fovDeg, nearPlane, farPlane);
	}

	Renderer::Renderer(ShaderProgram& shaderProgram, VertexArray& vao, GLsizei width, GLsizei height, GLfloat fovDeg /*= DefFOVDegrees*/, GLfloat nearPlane /*= DefNearPlane*/, GLfloat farPlane /*= DefFarPlane*/)
	{
		InitRenderer(width, height, fovDeg, nearPlane, farPlane);
		InitShaderProgram(shaderProgram);
		InitVAO(vao);
	}

	void Renderer::InitRenderer(GLsizei width, GLsizei height, GLfloat fovDeg, GLfloat nearPlane, GLfloat farPlane)
	{
		OnWindowResize(width, height);
		UpdateFOV(DefFOVDegrees);
		UpdateClipPlanes(nearPlane, farPlane);
		EnableColorBuffer();
		EnableDepthBuffer();
		SetClearColor();
	}

	void Renderer::SetViewPort(GLint left, GLint bottom, GLsizei width, GLsizei height)
	{
		GLCall(glViewport(left, bottom, width, height));
	}

	void Renderer::OnWindowResize(GLsizei newWidth, GLsizei newHeight)
	{
		m_Width = newWidth;
		m_Height = newHeight;
		m_AspectRatio = (double)m_Width / (double)m_Height;
		SetViewPort(m_Left, m_Bottom, m_Width, m_Height);
	}

	void Renderer::Draw()
	{
		if (m_IsInstanced)
			DrawInstanced();
		else
			GLCall(glDrawElements(GL_TRIANGLES, m_ElementCount, m_ElementDataType, nullptr));
	}


	static const std::vector<glm::vec3> positions{
	};
	void Renderer::DrawInstanced()
	{
		GLCall(glDrawElementsInstanced(GL_TRIANGLES, m_ElementCount, m_ElementDataType, nullptr, m_CurrentVAO->GetInstanceCount()));
	}

	void Renderer::UpdateClipPlanes(GLfloat nearPlane /*= NULL*/, GLfloat farPlane /*= NULL*/)
	{
		if (nearPlane != NULL)
			SetNearPlane(nearPlane);
		if (farPlane != NULL)
			SetFarPlane(farPlane);
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

	void Renderer::SetClearColor(glm::vec4 clearColor /*= glm::vec4(0.1, 0.1, 0, 1)*/)
	{
		GLCall(glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
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

	void Renderer::UpdateFOV(GLfloat fovDegrees)
	{
		m_FOVDegrees = fovDegrees;
		UpdateFOV();
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
		m_ElementCount = m_CurrentVAO->GetElementCount();
		m_ElementDataType = m_CurrentVAO->GetElementDataType();
		m_IsInstanced = m_CurrentVAO->GetElementCount() > 1;
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