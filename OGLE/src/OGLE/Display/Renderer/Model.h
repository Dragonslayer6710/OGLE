#pragma once

#include "OGLE/Display/Renderer/Mesh.h"
#include "OGLE/Display/Renderer/Shader.h"

namespace OGLE {
	class Model
	{
	public:
		static Scope<Model> Create(Ref<Mesh> mesh, Ref<Texture> texture = nullptr);

		Model(Ref<Mesh> mesh, Ref<Texture> texture = nullptr);
		~Model();

		void SetInstanceStats();

		void UpdateVAO();

		void Bind();

		void Unbind();

		void Draw(ShaderProgram* shaderProgram);

		GLuint GetID();

		Ref<Texture> GetTexture();

	protected:
		void InitVAO();

	private:
		static GLuint m_ModelCounter;
		GLuint m_ModelID = m_ModelCounter++;

		GLuint m_AttributeIDTracker;
		Ref<Mesh> m_Mesh;
		
		GLuint m_ElementCount;
		GLenum m_ElementDataType;

		GLuint m_InstanceCount = 1;
		bool m_IsInstanced = false;

		Scope<VertexArray> m_VAO;
		Ref<Texture> m_Texture;
	};

}
