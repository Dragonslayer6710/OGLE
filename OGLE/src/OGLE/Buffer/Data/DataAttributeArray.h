#pragma once

#include "OGLE/Buffer/Data/DataAttribute.h"

namespace OGLE {

	struct DataAttributeArray : DataAttribute
	{
		//DataAttribute* DataAttrib;
		DataAttributeArray
		(
			GLuint attribID,
			GLuint elementCount,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT
		)
			: DataAttribute(attribID, normalized, type, elementCount) {
			Size *= Count;
		}
	};

	struct DataAttributeMatrix : DataAttributeArray
	{
		//DataAttribute* DataAttrib;
		DataAttributeMatrix
		(
			GLuint attribID,
			GLuint elementCountX,
			GLuint elementCountY,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT
		)
			: DataAttributeArray(attribID, elementCountX * elementCountY, normalized, type) {}
	};

	namespace VEC2 {
		struct DataVec2 : DataAttributeArray
		{
			DataVec2(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: DataAttributeArray(attribID, 2, normalized, type) {}
		};

		struct DataFloat2 : DataVec2
		{
			DataFloat2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec2(attribID, normalized) {}
		};

		struct DataInt2 : DataVec2
		{
			DataInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec2(attribID, normalized, GL_INT) {}
		};

		struct DataUInt2 : DataVec2
		{
			DataUInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec2(attribID, normalized, GL_UNSIGNED_INT) {}
		};


		struct DataShort2 : DataVec2
		{
			DataShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec2(attribID, normalized, GL_SHORT) {}
		};

		struct DataUShort2 : DataVec2
		{
			DataUShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec2(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};
	}

	namespace VEC3 {
		struct DataVec3 : DataAttributeArray
		{
			DataVec3(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: DataAttributeArray(attribID, 3, normalized, type) {}
		};

		struct DataFloat3 : DataVec3
		{
			DataFloat3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec3(attribID, normalized) {}
		};

		struct DataInt3 : DataVec3
		{
			DataInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec3(attribID, normalized, GL_INT) {}
		};


		struct DataUInt3 : DataVec3
		{
			DataUInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec3(attribID, normalized, GL_UNSIGNED_INT) {}
		};

		struct DataShort3 : DataVec3
		{
			DataShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec3(attribID, normalized, GL_SHORT) {}
		};

		struct DataUShort3 : DataVec3
		{
			DataUShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec3(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};


	}

	namespace VEC4 {
		struct DataVec4 : DataAttributeArray
		{
			DataVec4(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: DataAttributeArray(attribID, 4, normalized, type) {}
		};

		struct DataFloat4 : DataVec4
		{
			DataFloat4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec4(attribID, normalized) {}
		};

		struct DataInt4 : DataVec4
		{
			DataInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec4(attribID, normalized, GL_INT) {}
		};

		struct DataUInt4 : DataVec4
		{
			DataUInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec4(attribID, normalized, GL_UNSIGNED_INT) {}
		};

		struct DataShort4 : DataVec4
		{
			DataShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec4(attribID, normalized, GL_SHORT) {}
		};


		struct DataUShort4 : DataVec4
		{
			DataUShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataVec4(attribID, normalized, GL_UNSIGNED_SHORT) {}
		};

	}

	namespace MAT3 {
		struct DataMat3 : DataAttributeMatrix
		{
			DataMat3(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: DataAttributeMatrix(attribID, 3, 3, normalized, type) {}
		};
		struct DataFloatMat3 : DataMat3
		{
			DataFloatMat3(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataMat3(attribID, normalized) {}
		};
	}

	namespace MAT4 {
		struct DataMat4 : DataAttributeMatrix
		{
			DataMat4(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
				: DataAttributeMatrix(attribID, 4, 4, normalized, type) {}
		};
		struct DataFloatMat4 : DataMat4
		{
			DataFloatMat4(GLuint attribID, GLboolean normalized = GL_FALSE)
				: DataMat4(attribID, normalized) {}
		};
	}

	using namespace VEC2;
	using namespace VEC3;
	using namespace VEC4;
	using namespace MAT3;
	using namespace MAT4;

	inline std::unordered_map<GLuint, GLuint> s_AttributeIDTrackers;

	static inline GLuint NewAttributeIDTracker()
	{
		GLuint id = s_AttributeIDTrackers.size();
		s_AttributeIDTrackers[id] = GLuint(0);
		return id;
	}

	static inline void DeleteAttributeIDTracker(GLuint id) {
		s_AttributeIDTrackers.erase(id);
	}

	static inline DataAttribute* GetNewDataAttribute(GLuint attributeIDTracker, DataAttributeType attribType, GLboolean normalized = GL_FALSE)
	{
		GLuint attribID = s_AttributeIDTrackers[attributeIDTracker];
		switch (attribType)
		{
		case FloatMat3:
			s_AttributeIDTrackers[attributeIDTracker] += 3;
			break;
		case FloatMat4:
			s_AttributeIDTrackers[attributeIDTracker] += 4;
			break;
		default:
			s_AttributeIDTrackers[attributeIDTracker] +=1;
		}
		switch (attribType)
		{
		case Float:
			return new DataFloat(attribID, normalized);
		case Float2:
			return new DataFloat2(attribID, normalized);
		case Float3:
			return new DataFloat3(attribID, normalized);
		case Float4:
			return new DataFloat4(attribID, normalized);
		case FloatMat3:
			return new DataFloatMat3(attribID, normalized);		
		case FloatMat4:
			return new DataFloatMat4(attribID, normalized);
		case Int:
			return new DataInt(attribID, normalized);
		case Int2:
			return new DataInt2(attribID, normalized);
		case Int3:
			return new DataInt3(attribID, normalized);
		case Int4:
			return new DataInt4(attribID, normalized);
		case UInt:
			return new DataUInt(attribID, normalized);
		case UInt2:
			return new DataUInt2(attribID, normalized);
		case UInt3:
			return new DataUInt3(attribID, normalized);
		case UInt4:
			return new DataUInt4(attribID, normalized);
		case Short:
			return new DataShort(attribID, normalized);
		case Short2:
			return new DataShort2(attribID, normalized);
		case Short3:
			return new DataShort3(attribID, normalized);
		case Short4:
			return new DataShort4(attribID, normalized);
		case UShort:
			return new DataUShort(attribID, normalized);
		case UShort2:
			return new DataUShort2(attribID, normalized);
		case UShort3:
			return new DataUShort3(attribID, normalized);
		case UShort4:
			return new DataUShort4(attribID, normalized);
		default:
			OGLE_CORE_ASSERT("INVALID ATTRIB TYPE");
			OGLE_ASSERT(true);
		}
	}

}

