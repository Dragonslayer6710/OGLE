#pragma once

#include "OGLE/Maths/Geometry/Vertex/VertexAttribute.h"

namespace OGLE {

	struct VertexAttributeArray : VertexAttribute
	{
		//VertexAttribute* VertexAttrib;
		VertexAttributeArray
		(
			GLuint attribID,
			GLuint count,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT
		)
			: VertexAttribute(attribID, normalized, type, count) {
			Size *= Count;
		}
	};

	namespace VEC2 {
		struct VertexVec2 : VertexAttributeArray
		{
			VertexVec2(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: VertexAttributeArray(attribID, 2, normalized, type) {}
		};

		struct VertexFloat2 : VertexVec2
		{
			VertexFloat2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec2(attribID, normalized) {}
		};

		struct VertexInt2 : VertexVec2
		{
			VertexInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec2(attribID, normalized, GL_INT) {}
		};

		struct VertexUInt2 : VertexVec2
		{
			VertexUInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec2(attribID, normalized, GL_UNSIGNED_INT) {}
		};


		struct VertexShort2 : VertexVec2
		{
			VertexShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec2(attribID, normalized, GL_SHORT) {}
		};

		struct VertexUShort2 : VertexVec2
		{
			VertexUShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec2(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};
	}

	namespace VEC3 {
		struct VertexVec3 : VertexAttributeArray
		{
			VertexVec3(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: VertexAttributeArray(attribID, 3, normalized, type) {}
		};

		struct VertexFloat3 : VertexVec3
		{
			VertexFloat3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec3(attribID, normalized) {}
		};

		struct VertexInt3 : VertexVec3
		{
			VertexInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec3(attribID, normalized, GL_INT) {}
		};


		struct VertexUInt3 : VertexVec3
		{
			VertexUInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec3(attribID, normalized, GL_UNSIGNED_INT) {}
		};

		struct VertexShort3 : VertexVec3
		{
			VertexShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec3(attribID, normalized, GL_SHORT) {}
		};

		struct VertexUShort3 : VertexVec3
		{
			VertexUShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec3(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};


	}

	namespace VEC4 {
		struct VertexVec4 : VertexAttributeArray
		{
			VertexVec4(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: VertexAttributeArray(attribID, 4, normalized, type) {}
		};

		struct VertexFloat4 : VertexVec4
		{
			VertexFloat4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec4(attribID, normalized) {}
		};

		struct VertexInt4 : VertexVec4
		{
			VertexInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec4(attribID, normalized, GL_INT) {}
		};

		struct VertexUInt4 : VertexVec4
		{
			VertexUInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec4(attribID, normalized, GL_UNSIGNED_INT) {}
		};

		struct VertexShort4 : VertexVec4
		{
			VertexShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec4(attribID, normalized, GL_SHORT) {}
		};


		struct VertexUShort4 : VertexVec4
		{
			VertexUShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: VertexVec4(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};

	}

	using namespace VEC2;
	using namespace VEC3;
	using namespace VEC4;

	static inline VertexAttribute* GetNewVertexAttribute(GLuint attribID, VertexAttributeType attribType, GLboolean normalized = GL_FALSE)
	{

		switch (attribType)
		{
		case VertAttribFloat:
			return new VertexFloat(attribID, normalized);
		case VertAttribFloat2:
			return new VertexFloat2(attribID, normalized);
		case VertAttribFloat3:
			return new VertexFloat3(attribID, normalized);
		case VertAttribFloat4:
			return new VertexFloat4(attribID, normalized);
		case VertAttribInt:
			return new VertexInt(attribID, normalized);
		case VertAttribInt2:
			return new VertexInt2(attribID, normalized);
		case VertAttribInt3:
			return new VertexInt3(attribID, normalized);
		case VertAttribInt4:
			return new VertexInt4(attribID, normalized);
		case VertAttribUInt:
			return new VertexUInt(attribID, normalized);
		case VertAttribUInt2:
			return new VertexUInt2(attribID, normalized);
		case VertAttribUInt3:
			return new VertexUInt3(attribID, normalized);
		case VertAttribUInt4:
			return new VertexUInt4(attribID, normalized);
		case VertAttribShort:
			return new VertexShort(attribID, normalized);
		case VertAttribShort2:
			return new VertexShort2(attribID, normalized);
		case VertAttribShort3:
			return new VertexShort3(attribID, normalized);
		case VertAttribShort4:
			return new VertexShort4(attribID, normalized);
		case VertAttribUShort:
			return new VertexUShort(attribID, normalized);
		case VertAttribUShort2:
			return new VertexUShort2(attribID, normalized);
		case VertAttribUShort3:
			return new VertexUShort3(attribID, normalized);
		case VertAttribUShort4:
			return new VertexUShort4(attribID, normalized);
		default:
			OGLE_CORE_ASSERT("INVALID ATTRIB TYPE");
			OGLE_ASSERT(true);
		}
	}

}

