#pragma once

#include "OGLE/Display/Renderer/Camera.h"
#include "OGLE/Display/Renderer/Model.h"

static const GLfloat DefFOVDegrees = 60.0f;
static const GLfloat DefNearPlane = 0.1f;
static const GLfloat DefFarPlane = 1000.0f;

namespace OGLE {

	class Renderer
	{
	public:

		Renderer(GLsizei width, GLsizei height, GLfloat fovDeg=DefFOVDegrees, GLfloat nearPlane=DefNearPlane, GLfloat farPlane=DefFarPlane);

		Renderer(ShaderProgram& shaderProgram, VertexArray& vao, GLsizei width, GLsizei height, GLfloat fovDeg = DefFOVDegrees, GLfloat nearPlane = DefNearPlane, GLfloat farPlane = DefFarPlane);

		~Renderer();

		// left/bottom = lower left corner of viewport rect (initial is 0,0), width/height is the dims of the rect
		void SetViewPort(GLint left, GLint bottom, GLsizei width, GLsizei height);

		void OnWindowResize(GLsizei newWidth, GLsizei newHeight);

		void UpdateFOV(GLfloat fovDegrees);
		
		GLfloat GetFOV() { return m_FOVRadians; }
		GLfloat GetFOVDegrees() { return m_FOVDegrees; }

		GLint GetLeft() { return m_Left; }
		GLint GetBottom() { return m_Bottom; }

		GLsizei GetWidth() { return m_Width; }
		GLsizei GetHeight() { return m_Height; }

		GLfloat GetAspectRatio() { return m_AspectRatio; }

		void UpdateClipPlanes(GLfloat nearPlane = NULL, GLfloat farPlane = NULL);

		GLfloat GetNearPlane() { return m_NearPlane; }
		GLfloat GetFarPlane() { return m_FarPlane; }

		void SetClearColor(glm::vec4 clearColor = glm::vec4(0.1, 0.1, 0, 1));

		void ChangeShaderProgram(ShaderProgram& shaderProgram);

		void Draw();

		void Clear();

		void AddModel(Ref<Model> model);

		void RemoveModel(Ref<Model> model);
		void RemoveModel(GLuint modelID);
		
	private:

		void UpdateFOV() { m_FOVRadians = glm::radians(m_FOVDegrees); }

		void EnableColorBuffer() { m_UseColorBuffer = true; }
		void DisableColorBuffer() { m_UseColorBuffer = false; }

		void EnableDepthBuffer() { m_UseDepthBuffer = true; glEnable(GL_DEPTH_TEST); }
		void DisableDepthBuffer() { m_UseDepthBuffer = false; }

		void EnableStencilBuffer(){ m_UseStencilBuffer = true; }
		void DisableStencilBuffer() { m_UseStencilBuffer = false; }

		void InitRenderer(GLsizei width, GLsizei height, GLfloat fovDeg, GLfloat nearPlane, GLfloat farPlane);

		void InitShaderProgram(ShaderProgram& shaderProgam);
		void SetShaderProgram(ShaderProgram& shaderProgram);
		void ActivateShaderProgram();
		void DeactivateShaderProgram();
		void ClearShaderProgram();

	private:

		GLfloat m_FOVDegrees;
		GLfloat m_FOVRadians;

		GLint m_Left = 0;
		GLint m_Bottom = 0;

		GLsizei m_Width;
		GLsizei m_Height;
		GLfloat m_AspectRatio;

		GLfloat m_NearPlane;
		GLfloat m_FarPlane;

		bool m_UseColorBuffer = false;
		bool m_UseDepthBuffer = false;
		bool m_UseStencilBuffer = false;

		ShaderProgram* m_CurrentShaderProgram = nullptr;
		std::unordered_map<GLuint, Ref<Model>> m_Models;

		GLuint m_ElementCount;
		GLenum m_ElementDataType;
		bool m_IsInstanced;
	};

}

