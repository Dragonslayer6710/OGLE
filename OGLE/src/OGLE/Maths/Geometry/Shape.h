#pragma once

#include "OGLE/Display/Renderer/Texture.h"
#include "OGLE/Buffer/VertexArray.h"

#include <variant>
namespace OGLE {

	template<typename T>
	static std::vector<T> CopyConstInit(const std::initializer_list<T>& vertices)
	{
		return std::vector<T>(vertices);
	}

	static std::vector<GLushort> CopyConstIndices(const std::vector<GLushort> indices)
	{
		return std::vector<GLushort>(indices);
	}


	class Shape
	{
	public:

		Ref<VertexCollection> GetVertices() { return m_Vertices; };
		std::vector<GLushort>* GetIndices() { return m_Vertices->GetIndices(); };

		Ref<InstanceCollection> GetInstances() 
		{ 
			return m_Instances;
		};

		template<typename T>
		static Scope<T> Create()
		{
			Scope<T> t = CreateScope<T>();
			t->SetVertexCollection();
			return t;
		}

		void ReserveInstances(GLuint size, GLuint compressedSize = 0)
		{
			if (compressedSize)
				compressedSize = size;
			m_Instances->ReserveInstances(size, compressedSize);
		}

		std::vector<Ref<Instance>>* GetSubset(size_t startIndex, size_t length)
		{
			return m_Instances->GetSubset(startIndex, length);
		}

		void AddInstances(std::vector<Instance>& instances)
		{
			return m_Instances->AddElements(instances);
		}

		template<std::size_t N>
		void AddInstances(const std::array<Instance, N>& instances)
		{
			return m_Instances->AddElements(instances);
		}

		void AddInstance(Instance& instance)
		{
			m_Instances->AddElement(instance);
		}

		void InsertInstance(GLuint index, Instance& instance)
		{
			m_Instances->InsertElement(index, instance);
		}

		void RemoveInstance(GLuint index)
		{
			m_Instances->RemoveElement(index);
		}

		Shape() 
		{			
			ContVector<Instance> instances;
			m_Instances = std::move(InstanceCollection::Create(instances));
		}
		~Shape()
		{

		}
	protected:

		template<std::size_t N, std::size_t M>
		Scope<VertexCollection> NewVertexCollection(const std::array<Vertex, N>& vertices, const std::array<GLushort, M>& indices)
		{
			// Convert std::array arguments to std::vector
			ContVector<Vertex> verticesVector;
			verticesVector.reserve(N); // Reserve space for N Vertices

			for (const Vertex& vertex : vertices) {
				verticesVector.emplace_back(vertex); // Store a pointer to the Vertex object
			}

			std::vector<GLushort> indicesVector(indices.begin(), indices.end());

			// Call VertexCollection::Create with both vectors
			return VertexCollection::Create(verticesVector, indicesVector);
		}


		virtual Scope<VertexCollection> NewVertexCollection() {
			return nullptr;
		}

		void SetVertexCollection() {
			m_Vertices = std::move(NewVertexCollection());
		}

		Ref<VertexCollection> m_Vertices;
		Ref<InstanceCollection> m_Instances;
	};

}

#include "OGLE/Maths/Geometry/Geometry2D.h"
#include "OGLE/Maths/Geometry/Geometry3D.h"