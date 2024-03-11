#include "oglepch.h"
#include "OGLE/Display/Renderer/Model.h"

namespace OGLE {

	Scope<Model> Model::Create(Ref<Mesh> mesh, Ref<Texture> texture)
	{
		return CreateScope<Model>(mesh, texture);
	}

	Model::Model(Ref<Mesh> mesh, Ref<Texture> texture)
		: m_AttributeIDTracker(NewAttributeIDTracker()),  m_Mesh(mesh), m_Texture(texture)
	{
		InitVAO();
	}

	Model::~Model()
	{
		DeleteAttributeIDTracker(m_AttributeIDTracker);
	}

	void Model::SetInstanceStats() {

		SetInstanceStats();
		
	}

	void Model::InitVAO()
	{
		Ref<VertexCollection> vertices = m_Mesh->GetVertices();
		Ref<InstanceCollection> instances = m_Mesh->GetInstances();

		vertices->LinkCollection(m_AttributeIDTracker);
		if (instances != nullptr) {
			instances->LinkCollection(m_AttributeIDTracker);
		}

		m_ElementCount = vertices->GetElementCount();
		m_ElementDataType = vertices->GetElementDataType();

		if (instances != nullptr) {
			m_InstanceCount = instances->GetLength();
			m_IsInstanced = m_InstanceCount;
		}
		m_VAO = VertexArray::Create(vertices, instances, true);
		UpdateVAO();
	}

	void Model::UpdateVAO(bool forceUpdate)
	{
		Ref<InstanceCollection> instances = m_Mesh->GetInstances();
		m_VAO->SetInstanceData(0, instances->GetCompressedSize(forceUpdate), instances->GetCompressedData(forceUpdate));
	}

	void Model::Bind()
	{
		m_VAO->Bind();
		if (m_Texture != nullptr)
		{
			m_SetTextureUniform = true;
			m_Texture->Bind();
		}
	}

	void Model::Unbind()
	{
		m_VAO->Unbind();
	}

	void Model::MFD()
	{
		m_MarkForDelete = true;
	}

	bool Model::CheckMFD()
	{
		return m_MarkForDelete;
	}

	void Model::Draw(ShaderProgram* shaderProgram)
	{
		Bind();
		if (m_SetTextureUniform) {
			shaderProgram->SetUniform1i("tex0", GetTexture()->GetTextureSlot());
			m_SetTextureUniform = false;
		}
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

	Ref<Texture> Model::GetTexture() {
		return m_Texture; 
	}

	GLuint Model::m_ModelCounter = 0;
}