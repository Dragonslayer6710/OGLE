#pragma once

#include "OGLE/Buffer/Data/DataAttributeArray.h"
#include <initializer_list>

namespace OGLE {

	struct DataLayout {
		std::vector<DataAttributeInfo> AttributeData;
		GLsizeiptr AttribCount;
		
		DataLayout() {}

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
			for (const DataAttributeType& attribType : attributeTypes)
				AttributeData.push_back(DataAttributeInfo(attribType));
			AttribCount = AttributeData.size();
		}
		
	};


	struct Vertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexUV;

    // Default constructor
    constexpr Vertex() : Position(0.0f), Color(1.0f), TexUV(0.0f) {}

    // Constructor with position, color, and texture UV
    constexpr Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texUV)
        : Position(position), Color(color), TexUV(texUV) {}

    // Constructor with position and texture UV (color defaults to white)
    constexpr Vertex(const glm::vec2& position, const glm::vec2& texUV)
        : Position(glm::vec3(position, 0.0f)), Color(1.0f), TexUV(texUV) {}

    // Check if the vertex is null
    constexpr bool IsNull() const { return false; }
};

	static const DataLayout s_VertexLayout = DataLayout({ Float3, Float4, Float2 });
	
	struct TextureGeometry {
		glm::vec2 Position;
		glm::vec2 Size;

		TextureGeometry(glm::vec2 position = glm::vec2(1.0f), glm::vec2 size = glm::vec2(1.0f))
			: Position(position), Size(size)
		{}		
	};

	

	struct Instance{
		glm::mat4 ModelMatrix;
		TextureGeometry TexGeometry;
		//bool isNull = false;

		Instance(glm::mat4 modelMatrix=glm::mat4(), TextureGeometry texGeom = TextureGeometry())
			: ModelMatrix(modelMatrix), TexGeometry(texGeom) {}

		// Copy constructor
		Instance(const Instance& other)
			: ModelMatrix(other.ModelMatrix), TexGeometry(other.TexGeometry) {
			// If any member requires deep copying, perform it here
		}

		Instance(Instance* otherInstance)
			: ModelMatrix(otherInstance->ModelMatrix), TexGeometry(otherInstance->TexGeometry) {}

		bool IsNull() {
			return ModelMatrix == glm::mat4(); }
	};
	

	static const DataLayout s_InstanceLayout = DataLayout({ FloatMat4, Float2, Float2 });

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
