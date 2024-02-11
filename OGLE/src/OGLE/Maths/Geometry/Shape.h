#pragma once

#include "OGLE/Buffer/VertexArray.h"

#include <variant>
namespace OGLE {

	static inline glm::mat4 NewModelMatrix(glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
	{
		return glm::scale(glm::translate(glm::mat4(1.0), translation) * glm::toMat4(rotation), scale);
	}
	static inline glm::mat4 NewModelMatrix(glm::vec3 translation = glm::vec3(1.0f), glm::vec3 rotDeg = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
	{
		return NewModelMatrix(translation, glm::quat(glm::radians(rotDeg)), scale);
	}

	class Shape
	{
	public:
		Shape
		(
			VertexCollection& m_Vertices, glm::vec3* position,
			glm::vec3* rotDeg, glm::vec3* scale, TextureGeometry* texGeom = new TextureGeometry()
		)
			: m_Vertices(&m_Vertices), m_Position(position), m_RotDeg(rotDeg), m_Scale(scale)
		{
		}

		VertexCollection* GetVertices() { return m_Vertices; }
		std::vector<GLushort>& GetIndices() { return m_Vertices->GetIndices(); }

	private:
		VertexCollection* m_Vertices;

		glm::vec3* m_Position;
		glm::vec3* m_RotDeg;
		glm::vec3* m_Scale;
	};

	class MultiShape
	{
	public:
		MultiShape(VertexCollection* vertices, InstanceList* instanceList, DataLayout instanceLayout = s_DefInstanceLayout)
			: m_Vertices(vertices)
		{
			m_Instances = new InstanceCollection(*instanceList, instanceLayout);
		}

		VertexCollection* GetVertices() { return m_Vertices; }
		InstanceCollection* GetInstances() { return m_Instances; }
	private:
		VertexCollection* m_Vertices;

		InstanceCollection* m_Instances;
	};
}



#include "OGLE/Maths/Geometry/3D/Cube.h"
#include "OGLE/Maths/Geometry/2D/Triangle.h"
#include "OGLE/Maths/Geometry/2D/Quad.h"