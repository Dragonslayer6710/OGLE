#pragma once

#include "OGLE/Geometry/Vertex/VertexAttributeArray.h"

namespace OGLE {

	struct VertexLayout {
		std::vector<VertexAttributeData>* AttributeData;
		GLsizeiptr AttribCount;

		VertexLayout(std::vector<VertexAttributeData>& attributeData)
			: AttributeData(&attributeData), AttribCount(AttributeData->size()) {}

		VertexLayout(std::vector<VertexAttributeType>& attributeTypes)
		{
			AttributeData = new std::vector<VertexAttributeData>();
			for (VertexAttributeType attribType : attributeTypes)
				AttributeData->push_back(VertexAttributeData(attribType));
			AttribCount = AttributeData->size();
		}
	};


	static const VertexLayout DefVertLayout = VertexLayout
	(
		std::vector<VertexAttributeType> {	VertAttribFloat3, VertAttribFloat4 }
	);


	struct Vertex {
		glm::vec3 Position;
		glm::vec4 Color;
	};

}
