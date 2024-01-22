#pragma once

#include "OGLE/Renderer/Shader.h"

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

		GLsizei GetWidth() { return m_Width; }
		GLsizei GetHeight() { return m_Width; }

		GLfloat GetAspectRatio() { return m_AspectRatio; }

		void SetClearColor(glm::vec4 clearColor);

		void ChangeShaderProgram(ShaderProgram& shaderProgram);
		void ChangeVAO(VertexArray& vao);

		void Draw();
		void Clear();
		
	private:

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
		GLint m_Left = 0;
		GLint m_Bottom = 0;
		GLsizei m_Width;
		GLsizei m_Height;

		GLfloat m_AspectRatio;

		bool m_UseColorBuffer = false;
		bool m_UseDepthBuffer = false;
		bool m_UseStencilBuffer = false;
		ShaderProgram* m_CurrentShaderProgram = nullptr;

		VertexArray* m_CurrentVAO = nullptr;
	};

}

