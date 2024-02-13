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

	template<typename T>
	static std::initializer_list<T> CopyConstInit(const std::initializer_list<T> vertices)
	{
		return std::initializer_list(vertices);
	}

	static std::vector<GLushort> CopyConstIndices(const std::vector<GLushort> indices)
	{
		return std::vector<GLushort>(indices);
	}



	class Shape
	{
	public:

		VertexCollection* GetVertices() { return m_Vertices; };
		std::vector<GLushort>* GetIndices() { return m_Vertices->GetIndices(); };

		InstanceCollection* GetInstances() { return m_Instances; };

		bool CheckInstanced() { return !m_Instances->IsEmpty(); }

		template<typename T>
		static T* Create()
		{
			return (T*) new Shape(T().NewVertexCollection());
		}

		virtual VertexCollection* NewVertexCollection() { return nullptr; }

		void AddInstances(std::vector<Instance>& instances)
		{
			return m_Instances->AddElements(instances);
		}

		void AddInstance(Instance instance)
		{
			m_Instances->AddElement(instance);
		}

		void InsertInstance(GLuint index, Instance instance)
		{
			m_Instances->InsertElement(index, instance);
		}

		void RemoveInstance(GLuint index)
		{
			m_Instances->RemoveElement(index);
		}

	protected:
		virtual Shape* Create(VertexCollection* vertices)
		{
			return new Shape(vertices);
		}

		Shape() = default;

		Shape
		(
			VertexCollection* vertices
		)
			: m_Vertices(vertices), m_Instances(new InstanceCollection()){}

		static VertexCollection* NewVertexCollection(const std::initializer_list<Vertex> vertices, const std::vector<GLushort> indices)
		{
			return new VertexCollection(CopyConstInit<Vertex>(vertices), CopyConstIndices(indices));
		}

		VertexCollection* m_Vertices;
		InstanceCollection* m_Instances;
	};

}

#include "OGLE/Maths/Geometry/Geometry2D.h"
#include "OGLE/Maths/Geometry/Geometry3D.h"