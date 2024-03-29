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
	}

	Renderer::~Renderer()
	{
		DeactivateShaderProgram();
	}

	void Renderer::InitRenderer(GLsizei width, GLsizei height, GLfloat fovDeg, GLfloat nearPlane, GLfloat farPlane)
	{
		// Enable face culling
		glEnable(GL_CULL_FACE);

		// Specify which faces to cull (back faces in this case)
		glCullFace(GL_BACK);
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
		std::vector<GLushort> modelsToDelete;
		for (auto& kv : m_Models) {
			if (!kv.second->CheckMFD())
				kv.second->Draw(m_CurrentShaderProgram);
			else
				modelsToDelete.push_back(kv.second->GetID());
		}
		if (!modelsToDelete.empty())
			for (GLushort id : modelsToDelete)
				RemoveModel(id);
	}

	void Renderer::UpdateClipPlanes(GLfloat nearPlane /*= NULL*/, GLfloat farPlane /*= NULL*/)
	{
		if (nearPlane != NULL)
			m_NearPlane = nearPlane;
		if (farPlane != NULL)
			m_FarPlane = farPlane;
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

	void Renderer::AddModel(Ref<Model> model)
	{
		m_Models[model->GetID()] = std::move(model);
	}

	void Renderer::RemoveModel(Ref<Model> model)
	{
		if (m_Models.find(model->GetID()) != m_Models.end())
			RemoveModel(model->GetID());
	}

	void Renderer::RemoveModel(GLuint modelID)
	{
		m_Models.erase(modelID);
	}

	void Renderer::DrawHUD()
	{
		for (const Ref<HUDElement>& hudElement : m_HUDElements)
			hudElement->Draw();
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
}