#pragma once

#include "OGLE/Maths/Geometry/Shape.h"
namespace OGLE
{
	class HUDElement
	{
		std::string m_ElementName;
		Scope<VertexArray> m_VAO;
		GLuint m_ElementCount;
	protected:
		GLuint m_AttributeIDTracker = -1;

	protected:
		void InitVAO(Ref<VertexCollection> vertices);

	public:
		HUDElement(std::string elementName)
			: m_AttributeIDTracker(NewAttributeIDTracker()), m_ElementName(elementName) {}

		std::string GetElementName() { return m_ElementName; }

		virtual void Draw();
	};

	class HUDCrosshair : public HUDElement
	{
		Scope<Cross> m_Crosshair;
	public:
		HUDCrosshair();

		void Draw() override;
	};

	class HUDViewRaycast : public HUDElement
	{
		Ref<glm::vec3> m_Position;
		Ref<glm::vec3> m_Orientation;
		float m_Distance;

		Scope<Line> m_Line;

	public:
		HUDViewRaycast(Ref<glm::vec3> position, Ref<glm::vec3> orientation, float distance);
		void Draw() override;
	};
}