#pragma once

#include "OGLE/Display/Renderer/Mesh.h"

namespace OGLE {
	class Model
	{
	public:
		static Ref<Model> Create(Ref<Shape> shape, Ref<Texture> texture);

		Model(Ref<Shape> shape, Ref<Texture> texture);

		void SetInstanceStats();
		void Draw();

		GLuint GetID();
		Ref <Texture> GetTexture();;

	protected:
		void Bind();

		void Unbind();
	private:
		static GLuint m_ModelCounter;

		GLuint m_ModelID = m_ModelCounter++;
		Ref<Mesh> m_Mesh;
		Ref<Texture> m_Texture;

		GLuint m_InstanceCount = 1;
		bool m_IsInstanced = false;

		GLuint m_ElementCount;
		GLenum m_ElementDataType;
	};
}
