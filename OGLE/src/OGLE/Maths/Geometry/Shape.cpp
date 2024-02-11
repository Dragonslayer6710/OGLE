#include "oglepch.h"
#include "OGLE/Maths/Geometry/Shape.h"

namespace OGLE {

	MultiShape* MultiShape::Create(VertexCollection* vertices, InstanceCollection* instances)
	{
		return new MultiShape(vertices, instances);
	}

	InstanceCollection* MultiShape::GetInstances()
	{
		return m_Instances;
	}

	MultiShape::MultiShape(VertexCollection* vertices, InstanceCollection* instances) : Shape(vertices), m_Instances(instances)
	{
		m_IsInstanced = true;
	}

	Shape* Shape::Create(VertexCollection* vertices, InstanceCollection* instances /*= nullptr*/)
	{
		if (instances != nullptr)
			return (Shape*)MultiShape::Create(vertices, instances);
		else
			return new Shape(vertices);
	}

	bool Shape::CheckInstanced()
	{
		return m_IsInstanced;
	}

	VertexCollection* Shape::GetVertices()
	{
		return m_Vertices;
	}

	std::vector<GLushort>& Shape::GetIndices()
	{
		return m_Vertices->GetIndices();
	}

	Shape::Shape(VertexCollection* vertices) : m_Vertices(vertices)
	{

	}

}



