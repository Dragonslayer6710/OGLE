#pragma once

#include "OGLE/Buffer/VertexArray.h"
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
			VertexCollection& vertices, std::vector<GLushort>& indices, glm::vec3* position,
			glm::vec3* rotDeg, glm::vec3* scale, TextureGeometry* texGeom = new TextureGeometry()
		)
			: m_Vertices(&vertices), m_Indices(&indices), m_Position(position), m_RotDeg(rotDeg), m_Scale(scale), m_TextureGeometry(texGeom)
		{
			RecalculateModelMatrix();
		}

		glm::vec3& GetPosition() { return *m_Position; }
		void Move(glm::vec3 moveMod) { SetPosition(*m_Position + moveMod); }

		glm::vec3& GetRotDeg() { return *m_RotDeg; }
		void Rotate(glm::vec3 rotMod) { SetRotDeg(*m_RotDeg + rotMod); }

		glm::vec3& GetScale() { return *m_Scale; }
		void Resize(glm::vec3 sizeMod) { SetScale(*m_Scale + sizeMod); }

		glm::mat4& GetModelMatrix() { return *m_ModelMatrix; }

	protected:

		void RecalculateModelMatrix() { m_ModelMatrix = &NewModelMatrix(*m_Position, *m_RotDeg, *m_Scale); }

		void SetPosition(glm::vec3 newPos) { *m_Position = newPos; RecalculateModelMatrix(); }
		void SetRotDeg(glm::vec3 newRotDeg) { *m_RotDeg = newRotDeg; RecalculateModelMatrix(); }
		void SetScale(glm::vec3 newScale) { *m_Scale = newScale; RecalculateModelMatrix(); }

	protected:
		friend class Mesh;
		VertexCollection* GetVertices() { return m_Vertices; }
		std::vector<GLushort>* GetIndices() { return m_Indices; }

	private:
		VertexCollection* m_Vertices;
		std::vector<GLushort>* m_Indices;

		glm::vec3* m_Position;
		glm::vec3* m_RotDeg;
		glm::vec3* m_Scale;

		glm::mat4* m_ModelMatrix;

		TextureGeometry* m_TextureGeometry;
	};
}

#include "OGLE/Maths/Geometry/3D/Cube.h"
#include "OGLE/Maths/Geometry/2D/Triangle.h"
#include "OGLE/Maths/Geometry/2D/Quad.h"