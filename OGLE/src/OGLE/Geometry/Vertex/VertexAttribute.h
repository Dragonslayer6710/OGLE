#pragma once

#include "Platform/OpenGL/OpenGLContext.h"

namespace OGLE {

	enum VertexAttributeType {
		VertAttribFloat,
		VertAttribFloat2,
		VertAttribFloat3,
		VertAttribFloat4,

		VertAttribInt,
		VertAttribInt2,
		VertAttribInt3,
		VertAttribInt4,

		VertAttribUInt,
		VertAttribUInt2,
		VertAttribUInt3,
		VertAttribUInt4,

		VertAttribShort,
		VertAttribShort2,
		VertAttribShort3,
		VertAttribShort4,

		VertAttribUShort,
		VertAttribUShort2,
		VertAttribUShort3,
		VertAttribUShort4,
	};

	struct VertexAttribute
	{
		GLuint AttribID; // Identifier for this attribute
		GLboolean Normalized; // Data needs to be normalised between -1/1 0/1 etc.
		GLenum Type; // Data type
		GLuint Count; // Number of elements this attribute covers
		GLsizei Size; // Size of Attribute in bytes
		VertexAttribute
		(
			GLuint attribID,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT,
			GLuint count = 1
		)
			: AttribID(attribID), Normalized(normalized), Type(type),
			Count(count), Size(sizeof(Type)) {}
	};

	struct VertexFloat : VertexAttribute
	{
		VertexFloat(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized) {}
	};

	struct VertexInt : VertexAttribute
	{
		VertexInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_INT) {}
	};

	struct VertexUInt : VertexAttribute
	{
		VertexUInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_UNSIGNED_INT) {}
	};	

	struct VertexShort : VertexAttribute
	{
		VertexShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_SHORT) {}
	};

	struct VertexUShort : VertexAttribute
	{
		VertexUShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};

	struct VertexAttributeData {
		VertexAttributeType Type;
		GLboolean Normalized;
		VertexAttributeData(VertexAttributeType type, GLboolean normalized = GL_FALSE)
			: Type(type), Normalized(normalized) {}
	};


}