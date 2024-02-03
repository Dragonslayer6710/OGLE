#pragma once

#include "OGLE/OGL/OpenGLContext.h"

namespace OGLE {

	enum DataAttributeType {
		Float,
		Float2,
		Float3,
		Float4,

		FloatMat3,
		FloatMat4,

		Int,
		Int2,
		Int3,
		Int4,

		UInt,
		UInt2,
		UInt3,
		UInt4,

		Short,
		Short2,
		Short3,
		Short4,

		UShort,
		UShort2,
		UShort3,
		UShort4,

	};

	struct DataAttribute
	{
		GLuint AttribID; // Identifier for this attribute
		GLboolean Normalized; // Data needs to be normalised between -1/1 0/1 etc.
		GLenum Type; // Data type
		GLuint Count; // Number of elements this attribute covers
		GLsizei Size; // Size of Attribute in bytes
		DataAttribute
		(
			GLuint attribID,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT,
			GLuint count = 1
		)
			: AttribID(attribID), Normalized(normalized), Type(type),
			Count(count), Size(sizeof(Type)) {}
	};

	struct DataFloat : DataAttribute
	{
		DataFloat(GLuint attribID, GLboolean normalized = GL_FALSE)
			: DataAttribute(attribID, normalized) {}
	};

	struct DataInt : DataAttribute
	{
		DataInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: DataAttribute(attribID, normalized, GL_INT) {}
	};

	struct DataUInt : DataAttribute
	{
		DataUInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: DataAttribute(attribID, normalized, GL_UNSIGNED_INT) {}
	};	

	struct DataShort : DataAttribute
	{
		DataShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: DataAttribute(attribID, normalized, GL_SHORT) {}
	};

	struct DataUShort : DataAttribute
	{
		DataUShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: DataAttribute(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};

	struct DataAttributeInfo {
		DataAttributeType m_ControlType;
		GLboolean Normalized;
		DataAttributeInfo(DataAttributeType type, GLboolean normalized = GL_FALSE)
			: m_ControlType(type), Normalized(normalized) {}
	
	};


}