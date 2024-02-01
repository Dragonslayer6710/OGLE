#pragma once

#include "OGLE/Buffer/Data/DataAttributeArray.h"
#include <initializer_list>

namespace OGLE {

	struct DataLayout {
		std::vector<DataAttributeInfo> AttributeData;
		GLsizeiptr AttribCount;

		DataLayout(std::initializer_list<DataAttributeInfo>& attributeData)
			: AttributeData(attributeData), AttribCount(AttributeData.size()) {}

		DataLayout(std::vector<DataAttributeInfo>& attributeData)
			: AttributeData(attributeData), AttribCount(AttributeData.size()) {}

		DataLayout(std::initializer_list<DataAttributeType> attributeTypes)
		{
			TypesToData(std::vector<DataAttributeType>(attributeTypes));
		}

		DataLayout(std::vector<DataAttributeType>& attributeTypes)
		{
			TypesToData(attributeTypes);
		}

	private:
		void TypesToData(std::vector<DataAttributeType>& attributeTypes)
		{
			for (DataAttributeType attribType : attributeTypes)
				AttributeData.push_back(DataAttributeInfo(attribType));
			AttribCount = AttributeData.size();
		}
		
	};

	static const DataLayout s_DefVertexLayout = DataLayout({ Float3, Float4, Float2 });	
	
	struct Vertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexUV;

		Vertex(glm::vec2 position, glm::vec4 color, glm::vec2 texUV)
			: Position(position.x, position.y, -1.0f), Color(color), TexUV(texUV) {}
		Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texUV)
			: Position(position), Color(color), TexUV(texUV) {}
	};

	class VertexCollection
	{
	public:
		VertexCollection(std::initializer_list<Vertex> vertices, DataLayout vertexLayout = s_DefVertexLayout)
			: m_Vertices(vertices), m_VertexLayout(s_DefVertexLayout)
		{
			InitAttributes();
		}	

		Vertex* GetData() {
			return m_Vertices.data();
		}
		GLuint GetSize() {
			return m_Vertices.size() * sizeof(Vertex);
		}
		DataLayout& GetLayout() {
			return m_VertexLayout;
		}

		GLuint GetStride() { return m_Stride; }

		GLuint GetAttribCount() { return m_AttribCount; }

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_VertexAttributes; }

	private:
		void InitAttributes() {
			for (DataAttributeInfo attribData : GetLayout().AttributeData) {
				m_VertexAttributes[m_Stride] = GetNewDataAttribute(m_AttribCount++, attribData.m_ControlType, attribData.Normalized);
				m_Stride += m_VertexAttributes[m_Stride]->Size;
			}
		}

	private:
		std::vector<Vertex> m_Vertices;
		DataLayout m_VertexLayout;

		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;
		std::unordered_map<GLuint, DataAttribute*> m_VertexAttributes;
	};

	static const DataLayout s_DefInstanceDataLayout = DataLayout({ FloatMat4 });


	struct InstanceData {
		glm::mat4 ModelTransform;
		//GLuint SubTextureID;
	};

	class InstanceDataCollection
	{
	public:
		InstanceDataCollection(std::initializer_list<InstanceData> instanceData, DataLayout instanceDataLayout = s_DefInstanceDataLayout)
			: m_InstanceData(instanceData), m_InstanceDataLayout(instanceDataLayout) 
		{
			InitAttributes();
		}

		InstanceData* GetData() {
			return m_InstanceData.data();
		}
		GLuint GetSize() {
			return m_InstanceData.size() * sizeof(InstanceData);
		}
		DataLayout& GetLayout() {
			return m_InstanceDataLayout;
		}
		GLuint GetStride() { return m_Stride; }

		GLuint GetAttribCount() { return m_AttribCount; }

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_InstanceDataAttributes; }

	private:
		void InitAttributes() {
			for (DataAttributeInfo attribData : GetLayout().AttributeData) {
				m_InstanceDataAttributes[m_Stride] = GetNewDataAttribute(m_AttribCount++, attribData.m_ControlType, attribData.Normalized);
				m_Stride += m_InstanceDataAttributes[m_Stride]->Size;
			}
		}

	private:
		std::vector<InstanceData> m_InstanceData;
		DataLayout m_InstanceDataLayout;

		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;
		std::unordered_map<GLuint, DataAttribute*> m_InstanceDataAttributes;
	};


}
