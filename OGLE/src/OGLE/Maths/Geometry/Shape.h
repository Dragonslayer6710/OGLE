#pragma once

#include "OGLE/Display/Renderer/Texture.h"
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
		static Shape* Create(VertexCollection* vertices, InstanceCollection* instances = nullptr);

		bool CheckInstanced();

		VertexCollection* GetVertices();
		std::vector<GLushort>& GetIndices();

	protected:
		Shape
		(
			VertexCollection* vertices
		);

	protected:
		bool m_IsInstanced = false;

		VertexCollection* m_Vertices;
	};

	class MultiShape : public Shape
	{
	public:
		InstanceCollection* GetInstances();

		static MultiShape* Create(VertexCollection* vertices, InstanceCollection* instances);
	protected:
		MultiShape(VertexCollection* vertices, InstanceCollection* instances);


	private:
		InstanceCollection* m_Instances;
	};

}

#include "OGLE/Maths/Geometry/3D/Cube.h"
#include "OGLE/Maths/Geometry/2D/Triangle.h"
#include "OGLE/Maths/Geometry/2D/Quad.h"