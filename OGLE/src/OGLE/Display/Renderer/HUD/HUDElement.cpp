#include "oglepch.h"
#include "OGLE/Display/Renderer/HUD/HUDElement.h"
#include "OGLE/Core/Application.h"

namespace OGLE
{
	void HUDElement::InitVAO(Ref<VertexCollection> vertices)
	{
		vertices->LinkCollection(m_AttributeIDTracker);

		m_VAO = VertexArray::Create(vertices);
		m_ElementCount = vertices->GetElementCount();
	}

	void HUDElement::Draw()
	{
		m_VAO->Bind();
		GLCall(glDrawElements(GL_LINES, m_ElementCount, GL_UNSIGNED_SHORT, nullptr));
		m_VAO->Unbind();
	}

	HUDCrosshair::HUDCrosshair()
		: HUDElement("Crosshair"), m_Crosshair(Cross::Create(2.0f))
	{
		InitVAO(m_Crosshair->GetVertices());
	}
	void HUDCrosshair::Draw()
	{
		GLCall(glLineWidth(m_Crosshair->GetThickness()));
		HUDElement::Draw();
		GLCall(glLineWidth(1.0f));
	}

	HUDViewRaycast::HUDViewRaycast(Ref<glm::vec3> position, Ref<glm::vec3> orientation, float distance)
		: HUDElement("View Raycast"), m_Position(position), m_Orientation(orientation), m_Distance(distance)
	{}

    void HUDViewRaycast::Draw()
    {
        // Calculate the end point of the raycast
		std::vector<glm::vec3> rcVecs = Raycast(*m_Position, glm::normalize(*m_Orientation), m_Distance).GetVectors();

        // Calculate the start point of the raycast (considering it starts from the camera)
        glm::vec3 start = *m_Position;
        glm::vec3 end = rcVecs[2];
		m_Line = Line::Create(start, end);
		if (m_AttributeIDTracker == -1)
			m_AttributeIDTracker = NewAttributeIDTracker();
		InitVAO(m_Line->GetVertices());
		HUDElement::Draw();
		m_AttributeIDTracker = -1;
    }



}
