#pragma once

#include "OGLE/Maths/Geometry/Mesh.h"

namespace OGLE {
	class Model {
	public:
		Model(Texture* texture)
			: m_Texture(texture) {}


		void AddQuadCuboid(GLushort subTexIDs[6], glm::mat4 modelMatrix = glm::mat4(1.0f))
		{

			const char* shapeName = typeid(QuadCuboid).name();
			if (m_ShapeMeshes.find(shapeName) == m_ShapeMeshes.end()) {
				m_Shapes[shapeName] = ((Shape*)QuadCuboid::Create(m_Texture, subTexIDs, modelMatrix));
				m_ShapeMeshes[shapeName] = Mesh::Create(m_Shapes[shapeName]);
			}
			else
			{
				std::vector<Instance>* A = ((QuadCuboid*)m_Shapes[shapeName])->GetInstances()->GetDataList().GetDataVector();
				std::vector<Instance>* B = NewQuadCuboidInstanceList(m_Texture, subTexIDs, modelMatrix)->GetDataVector();
				
				std::vector<Instance>* AB = new std::vector<Instance>();
				AB->reserve(A->size() + B->size());
				AB->insert(AB->end(), A->begin(), A->end());
				AB->insert(AB->end(), B->begin(), B->end());

				GetVAO().SetInstanceBuffer(new InstanceCollection(InstanceList(AB)));
			}
		}

		void AddQuadCuboid(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotDeg = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f), GLushort subTexIDs[6] = nullptr)
		{
			AddQuadCuboid(subTexIDs, NewModelMatrix(position, rotDeg, scale));
		}

		VertexArray& GetVAO() {
			return *m_ShapeMeshes[typeid(QuadCuboid).name()]->GetVAO();
		}

	private:
		Texture* m_Texture;
		std::unordered_map<const char*, Shape*> m_Shapes;
		std::unordered_map<const char*, Mesh*> m_ShapeMeshes;
	};
}
