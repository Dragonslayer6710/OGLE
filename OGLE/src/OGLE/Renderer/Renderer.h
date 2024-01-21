#pragma once

#include "OGLE/Renderer/Shader.h"

namespace OGLE {

	class Renderer
	{
	public:

		Renderer() { }

		Renderer(ShaderProgram& shaderProgram, VertexArray& vao) { InitRenderer(shaderProgram, vao); }

		~Renderer(){
			DeactivateShaderProgram();
			UnbindVAO();
		}

		void Draw();

		void SetClearColor(glm::vec4 clearColor);
		void Clear();

		void ChangeShaderProgram(ShaderProgram& shaderProgram);
		void ChangeVAO(VertexArray& vao);
		
	private:

		void EnableColorBuffer() { m_UseColorBuffer = true; }
		void DisableColorBuffer() { m_UseColorBuffer = false; }

		void EnableDepthBuffer() { m_UseDepthBuffer = true; glEnable(GL_DEPTH_TEST); }
		void DisableDepthBuffer() { m_UseDepthBuffer = false; }

		void EnableStencilBuffer(){ m_UseStencilBuffer = true; }
		void DisableStencilBuffer() { m_UseStencilBuffer = false; }

		void InitRenderer(ShaderProgram& shaderProgram, VertexArray& vao);

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
		bool m_UseColorBuffer = false;
		bool m_UseDepthBuffer = false;
		bool m_UseStencilBuffer = false;
		ShaderProgram* m_CurrentShaderProgram = nullptr;

		VertexArray* m_CurrentVAO = nullptr;
	};

}

