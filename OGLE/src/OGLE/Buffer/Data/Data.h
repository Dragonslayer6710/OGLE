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

		Vertex()
			: Position(glm::vec3()), Color(glm::vec4()), TexUV(glm::vec2()) {}
		Vertex(glm::vec2 position, glm::vec4 color, glm::vec2 texUV)
			: Position(position, -1.0f), Color(color), TexUV(texUV) {}
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

		GLuint GetLength() {
			return m_Vertices.size();
		}

		DataLayout& GetLayout() {
			return m_VertexLayout;
		}

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_VertexAttributes; }

	private:
		void InitAttributes() {
			GLuint offset = 0;
			GLuint attribCount = 0;
			for (DataAttributeInfo attribData : GetLayout().AttributeData) {
				m_VertexAttributes[offset] = GetNewDataAttribute(attribCount++, attribData.m_ControlType, attribData.Normalized);
				offset += m_VertexAttributes[offset]->Size;
			}
		}

	private:
		std::vector<Vertex> m_Vertices;
		DataLayout m_VertexLayout;

		std::unordered_map<GLuint, DataAttribute*> m_VertexAttributes;
	};

	static const DataLayout s_DefInstanceDataLayout = DataLayout({ FloatMat4, Float2, Float2 });


	struct InstanceData {
		glm::mat4 ModelTransform;
		glm::vec2 SubTexOffset = glm::vec2(0,0);
		glm::vec2 SubTexSize = glm::vec2(1, 1);
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

		GLuint GetInstanceCount() {
			return m_InstanceData.size();
		}

		DataLayout& GetLayout() {
			return m_InstanceDataLayout;
		}

		std::unordered_map<GLuint, DataAttribute*> GetAttributes() { return m_InstanceDataAttributes; }

	private:
		void InitAttributes() {
			GLuint offset = 0;
			GLuint attribCount = 0;
			for (DataAttributeInfo attribData : GetLayout().AttributeData) {
				m_InstanceDataAttributes[offset] = GetNewDataAttribute(attribCount++, attribData.m_ControlType, attribData.Normalized);
				offset += m_InstanceDataAttributes[offset]->Size;
			}
		}

	private:
		std::vector<InstanceData> m_InstanceData;
		DataLayout m_InstanceDataLayout;

		std::unordered_map<GLuint, DataAttribute*> m_InstanceDataAttributes;
	};


}
