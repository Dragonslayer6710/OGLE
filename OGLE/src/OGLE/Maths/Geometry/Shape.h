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
			VertexCollection& Vertices, glm::vec3* position,
			glm::vec3* rotDeg, glm::vec3* scale, TextureGeometry* texGeom = new TextureGeometry()
		)
			: m_Vertices(&Vertices), m_Position(position), m_RotDeg(rotDeg), m_Scale(scale), m_InstanceData(new Instance())
		{
			RecalculateModelMatrix();
			m_InstanceData->TexGeometry = *texGeom;
		}

		glm::vec3& GetPosition() { return *m_Position; }
		void Move(glm::vec3 moveMod) { SetPosition(*m_Position + moveMod); }

		glm::vec3& GetRotDeg() { return *m_RotDeg; }
		void Rotate(glm::vec3 rotMod) { SetRotDeg(*m_RotDeg + rotMod); }

		glm::vec3& GetScale() { return *m_Scale; }
		void Resize(glm::vec3 sizeMod) { SetScale(*m_Scale + sizeMod); }

		Instance& GetInstanceData() { return *m_InstanceData; }

		VertexCollection* GetVertices() { return m_Vertices; }
		std::vector<GLushort>& GetIndices() { return m_Vertices->GetIndices(); }

		void SetTexGeom(TextureGeometry texGeom) { m_InstanceData->TexGeometry = texGeom; }

	protected:

		void RecalculateModelMatrix() { m_InstanceData->ModelMatrix = NewModelMatrix(*m_Position, *m_RotDeg, *m_Scale); }

		void SetPosition(glm::vec3 newPos) { *m_Position = newPos; RecalculateModelMatrix(); }
		void SetRotDeg(glm::vec3 newRotDeg) { *m_RotDeg = newRotDeg; RecalculateModelMatrix(); }
		void SetScale(glm::vec3 newScale) { *m_Scale = newScale; RecalculateModelMatrix(); }

	protected:
		Instance* m_InstanceData;

	private:
		VertexCollection* m_Vertices;

		glm::vec3* m_Position;
		glm::vec3* m_RotDeg;
		glm::vec3* m_Scale;
	};

	struct MultiShape
	{
		std::vector <const char*> ShapeNames;
		std::vector<Vertex> VertexVector;

		std::vector<GLushort> Indices;
		std::unordered_map<const char*, InstanceList*> ShapeInstanceLists;
		std::unordered_map<const char*, DataLayout> ShapeInstanceLayouts;

		VertexCollection* Vertices;
		InstanceCollection* Instances;

	protected:
		void RegisterShapes(std::vector<Shape*> shapes, DataLayout instanceLayout = s_DefInstanceLayout)
		{
			for (int i = 0; i < shapes.size(); i++)
				RegisterShape(shapes[i], instanceLayout);
		}

		void PrepareMeshData()
		{
			VertexList* vertexList = new VertexList(&VertexVector);
			Vertices = new VertexCollection(*vertexList, &Indices);

			std::vector<Instance>* combinedInstances = new std::vector<Instance>();

			InstanceList* instanceList;
			GLuint index = 0;

			for (const char* shapeName : ShapeNames) {
				std::vector<Instance>* subInstanceList = ShapeInstanceLists[shapeName]->GetDataVector();
				combinedInstances->reserve(combinedInstances->size() + subInstanceList->size());
				combinedInstances->insert(combinedInstances->end(), subInstanceList->begin(), subInstanceList->end());
			}
			instanceList = new InstanceList(combinedInstances);
			Instances = new InstanceCollection(*instanceList);
		}

	private:
		void RegisterShape(Shape* shape, DataLayout instanceDataLayout)
		{
			const char* shapeName = typeid(*shape).name();
			if (std::find(ShapeNames.begin(), ShapeNames.end(), shapeName) == ShapeNames.end()) {
				ShapeNames.push_back(shapeName);

				std::vector<Vertex>* shapeVerts = 
					new std::vector<Vertex>(
						(Vertex*)shape->GetVertices()->GetData(), 
						(Vertex*)shape->GetVertices()->GetData()+shape->GetVertices()->GetLength()
					);
				GLushort relativeFirst = VertexVector.size();

				VertexVector.reserve(VertexVector.size() + shapeVerts->size());
				VertexVector.insert(VertexVector.end(), shapeVerts->begin(), shapeVerts->end());

				std::vector<GLushort>* shapeIndices = &shape->GetIndices();
				std::for_each(shapeIndices->begin(), shapeIndices->end(), [relativeFirst](GLushort& d) {d += relativeFirst; });

				Indices.reserve(Indices.size() + shapeIndices->size());
				Indices.insert(Indices.end(), shapeIndices->begin(), shapeIndices->end());

				ShapeInstanceLists[shapeName] = new InstanceList();
				ShapeInstanceLayouts[shapeName] = instanceDataLayout;
			}
			ShapeInstanceLists[shapeName]->push_back(shape->GetInstanceData());
		}
	};
}



#include "OGLE/Maths/Geometry/3D/Cube.h"
#include "OGLE/Maths/Geometry/2D/Triangle.h"
#include "OGLE/Maths/Geometry/2D/Quad.h"