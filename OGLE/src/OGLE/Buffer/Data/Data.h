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

	

	struct Vertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexUV;

		Vertex()
			: Position(glm::vec3()), Color(glm::vec4()), TexUV(glm::vec2()) {}
		Vertex(glm::vec2 position, glm::vec4 color, glm::vec2 texUV)
			: Position(position, 0.0f), Color(color), TexUV(texUV) {}
		Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texUV)
			: Position(position), Color(color), TexUV(texUV) {}
	};

	static const DataLayout s_DefVertexLayout = DataLayout({ Float3, Float4, Float2 });
	

	

	struct Instance {
		glm::mat4 ModelTransform;
		glm::vec2 SubTexOffset = glm::vec2(0,0);
		glm::vec2 SubTexSize = glm::vec2(1, 1);

		Instance() {}
		Instance(glm::mat4 modelTransform, glm::vec2 subTexOffset = glm::vec2(0, 0), glm::vec2 subTexSize = glm::vec2(1, 1))
			:ModelTransform(modelTransform), SubTexOffset(subTexOffset), SubTexSize(subTexSize)
		{
			OGLE_INFO("");
		}
	};

	static const DataLayout s_DefInstanceLayout = DataLayout({ FloatMat4, Float2, Float2 });


	

	template <typename T>
	class DataList
	{
	public:
		GLvoid* GetData() {
			return m_Data->data();
		}

		GLuint GetLength() {
			return m_Data->size();
		}

		GLuint GetSize() {
			return m_Data->size() * sizeof(T);
		}

		std::vector<T>& GetDataVector() {
			return *m_Data;
		}

	protected:
		DataList(std::initializer_list<T> data)
			: DataList(new std::vector<T>(data)) {}

	private:
		DataList(std::vector<T>* data)
			: m_Data(data) {}

	private:
		std::vector<T>* m_Data;
	};

	class VertexList : public DataList<Vertex>
	{
	public:
		VertexList(std::initializer_list<Vertex> data)
			:DataList(data) {}
	};

	class InstanceList : public DataList<Instance>
	{
	public:
		InstanceList(std::initializer_list<Instance> data)
			:DataList(data) {}
	};

	/*class C
	{
	public:

	protected:
		C(std::initializer_list<int> data)
			: C(new std::vector<int>(data)) {}

	private:
		C(std::vector<int>* data)
			: m_Data(data) {}

	private:
		std::vector<int>* m_Data;
	};

	class A : public C
	{
	public:
		A(std::initializer_list<int> data)
			:C(data) {}
	};

	class InstanceList : public C
	{
	public:
		InstanceList(std::initializer_list<int> data)
			:C(data) {}
	};*/
}
