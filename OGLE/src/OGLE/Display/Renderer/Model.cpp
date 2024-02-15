#include "oglepch.h"
#include "OGLE/Display/Renderer/Model.h"

namespace OGLE {

	OGLE::Ref<OGLE::Model> Model::Create(Ref<Shape> shape, Ref<Texture> texture)
	{
		return CreateRef<Model>(shape, texture);
	}

	Model::Model(Ref<Shape> shape, Ref<Texture> texture) 
		: m_Mesh(Mesh::Create(shape)), m_Texture(texture)
	{
		Ref<VertexCollection> vertices = m_Mesh->GetVAO()->GetVertices();
		m_ElementCount = vertices->GetElementCount();
		m_ElementDataType = vertices->GetElementDataType();
		
		SetInstanceStats();		
	}

	void Model::SetInstanceStats() {
		Ref<InstanceCollection> instances = m_Mesh->GetVAO()->GetInstances();
		if (instances != nullptr) {
			m_InstanceCount = instances->GetLength();
			m_IsInstanced = m_InstanceCount;
		}
	}

	void Model::Draw()
	{
		Bind();
		if (m_IsInstanced) {
			GLCall(glDrawElementsInstanced(GL_TRIANGLES, m_ElementCount, m_ElementDataType, nullptr, m_InstanceCount));
		}
		else {
			GLCall(glDrawElements(GL_TRIANGLES, m_ElementCount, m_ElementDataType, nullptr));
		}
		Unbind();
	}

	GLuint Model::GetID()
	{
		return m_ModelID;
	}

	OGLE::Ref <OGLE::Texture> Model::GetTexture()
	{
		return m_Texture;
	}

	void Model::Bind()
	{
		m_Texture->Bind();
		m_Mesh->Bind();
	}

	void Model::Unbind()
	{
		m_Texture->Unbind();
		m_Mesh->Unbind();
	}

	GLuint Model::m_ModelCounter = 0;
}