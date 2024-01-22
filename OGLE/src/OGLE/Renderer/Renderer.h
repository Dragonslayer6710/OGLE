#pragma once

#include "OGLE/Renderer/Shader.h"
static const GLfloat DefFOVDegrees = 60.0f;
namespace OGLE {

	class Renderer
	{
	public:

		Renderer(GLsizei width, GLsizei height);

		Renderer(GLsizei width, GLsizei height, ShaderProgram& shaderProgram, VertexArray& vao);

		~Renderer(){
			DeactivateShaderProgram();
			UnbindVAO();
		}

		// left/bottom = lower left corner of viewport rect (initial is 0,0), width/height is the dims of the rect
		void SetViewPort(GLint left, GLint bottom, GLsizei width, GLsizei height);

		void OnWindowResize(GLsizei newWidth, GLsizei newHeight);

		void UpdateFOV(GLfloat fovDegrees);
		
		GLfloat GetFOV() { return m_FOVRadians; }

		GLint GetLeft() { return m_Left; }
		GLint GetBottom() { return m_Bottom; }

		GLsizei GetWidth() { return m_Width; }
		GLsizei GetHeight() { return m_Width; }

		GLfloat GetAspectRatio() { return m_AspectRatio; }

		GLfloat GetNearPlane() { return m_NearPlane; }
		GLfloat GetFarPlane() { return m_FarPlane; }

		void SetClearColor(glm::vec4 clearColor);

		void ChangeShaderProgram(ShaderProgram& shaderProgram);
		void ChangeVAO(VertexArray& vao);

		void Draw();
		void Clear();
		
	private:

		void UpdateFOV() { m_FOVRadians = glm::radians(m_FOVDegrees); }

		void EnableColorBuffer() { m_UseColorBuffer = true; }
		void DisableColorBuffer() { m_UseColorBuffer = false; }

		void EnableDepthBuffer() { m_UseDepthBuffer = true; glEnable(GL_DEPTH_TEST); }
		void DisableDepthBuffer() { m_UseDepthBuffer = false; }

		void EnableStencilBuffer(){ m_UseStencilBuffer = true; }
		void DisableStencilBuffer() { m_UseStencilBuffer = false; }

		void InitRenderer(GLsizei width, GLsizei height);

		void InitShaderProgram(ShaderProgram& shaderProgam);
		void SetShaderProgram(ShaderProgram& shaderProgram);
		void ActivateShaderProgram();
		void DeactivateShaderProgram();
		void ClearShaderProgram();

		void InitVAO(VertexArray& vao);
		void SetVAO(VertexArray& vao);
		void BindVAO();
		void UnbindVAO();
		void ClearVAO();
	private:

		GLfloat m_FOVDegrees;
		GLfloat m_FOVRadians;

		GLint m_Left = 0;
		GLint m_Bottom = 0;

		GLsizei m_Width;
		GLsizei m_Height;
		GLfloat m_AspectRatio;

		GLfloat m_NearPlane = 0.1f;
		GLfloat m_FarPlane = 10.0f;

		bool m_UseColorBuffer = false;
		bool m_UseDepthBuffer = false;
		bool m_UseStencilBuffer = false;
		ShaderProgram* m_CurrentShaderProgram = nullptr;

		VertexArray* m_CurrentVAO = nullptr;
	};

}

