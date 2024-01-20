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
		GLsizei Count; // Number of elements this attribute covers
		GLuint Size; // Size of Attribute in bytes
		VertexAttribute
		(
			GLuint attribID,
			GLboolean normalized = GL_FALSE,
			GLenum type = GL_FLOAT,
			GLsizei count = 1
		)
			: AttribID(attribID), Normalized(normalized), Type(type),
			Count(count), Size(sizeof(Type)) {}
	};

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
			Size = Size * Count;
		}
	};

	struct VertexVec2 : VertexAttributeArray
	{
		VertexVec2(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
			: VertexAttributeArray(attribID, 2, normalized, type) {}
	};

	struct VertexVec3 : VertexAttributeArray
	{
		VertexVec3(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
			: VertexAttributeArray(attribID, 3, normalized, type) {}
	};

	struct VertexVec4 : VertexAttributeArray
	{
		VertexVec4(GLuint attribID, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT)
			: VertexAttributeArray(attribID, 4, normalized, type) {}
	};

	struct VertexFloat : VertexAttribute
	{
		VertexFloat(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized) {}
	};

	struct VertexFloat2 : VertexVec2
	{
		VertexFloat2(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec2(attribID, normalized) {}
	};

	struct VertexFloat3 : VertexVec3
	{
		VertexFloat3(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec3(attribID, normalized) {}
	};

	struct VertexFloat4 : VertexVec4
	{
		VertexFloat4(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec4(attribID, normalized) {}
	};

	struct VertexInt : VertexAttribute
	{
		VertexInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_INT) {}
	};

	struct VertexInt2 : VertexVec2
	{
		VertexInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec2(attribID, normalized, GL_INT) {}
	};

	struct VertexInt3 : VertexVec3
	{
		VertexInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec3(attribID, normalized, GL_INT) {}
	};

	struct VertexInt4 : VertexVec4
	{
		VertexInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec4(attribID, normalized, GL_INT) {}
	};

	struct VertexUInt : VertexAttribute
	{
		VertexUInt(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_UNSIGNED_INT) {}
	};

	struct VertexUInt2 : VertexVec2
	{
		VertexUInt2(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec2(attribID, normalized, GL_UNSIGNED_INT) {}
	};

	struct VertexUInt3 : VertexVec3
	{
		VertexUInt3(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec3(attribID, normalized, GL_UNSIGNED_INT) {}
	};

	struct VertexUInt4 : VertexVec4
	{
		VertexUInt4(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec4(attribID, normalized, GL_UNSIGNED_INT) {}
	};

	struct VertexShort : VertexAttribute
	{
		VertexShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_SHORT) {}
	};

	struct VertexShort2 : VertexVec2
	{
		VertexShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec2(attribID, normalized, GL_SHORT) {}
	};

	struct VertexShort3 : VertexVec3
	{
		VertexShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec3(attribID, normalized, GL_SHORT) {}
	};

	struct VertexShort4 : VertexVec4
	{
		VertexShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec4(attribID, normalized, GL_SHORT) {}
	};

	struct VertexUShort : VertexAttribute
	{
		VertexUShort(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexAttribute(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};

	struct VertexUShort2 : VertexVec2
	{
		VertexUShort2(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec2(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};

	struct VertexUShort3 : VertexVec3
	{
		VertexUShort3(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec3(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};

	struct VertexUShort4 : VertexVec4
	{
		VertexUShort4(GLuint attribID, GLboolean normalized = GL_FALSE)
			: VertexVec4(attribID, normalized, GL_UNSIGNED_SHORT) {}
	};


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

	struct Vertex {
		glm::vec2 position;
		glm::vec4 color;
	};

	class Buffer
	{
	public:
		Buffer(GLenum bufferTarget, void* data, GLuint size,GLenum bufferUsage = GL_STATIC_DRAW) 
			: m_BufferTarget(bufferTarget), m_BufferUsage(bufferUsage) {
			Init(); SetData(data, size);
		};

		// Buffer referenced by m_ID no longer needed, so deleted
		~Buffer() { GLCall(glDeleteBuffers(1, &m_ID)); }

		// Buffer referenced by m_ID is bound to the usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.)
		void Bind() const { GLCall(glBindBuffer(m_BufferTarget, m_ID)); }

		// Buffer usage location (GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER etc.) is unbound from any pointer
		void Unbind() const { GLCall(glBindBuffer(m_BufferTarget, 0)); }

		GLuint GetSize() { return m_Size; }
		virtual void UpdateData(void* data, GLuint size);

	protected:
		// Add Data to Buffer
		void SetData(void* data, GLuint size);

	private:
		// Generate a buffer referenced by m_ID
		void Init() { GLCall(glGenBuffers(1, &m_ID)); }

	protected:
		GLuint m_ID;
		GLuint m_Size;

	private:
		GLenum m_BufferTarget;
		GLenum m_BufferUsage;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(void* data, GLuint size) : Buffer(GL_ARRAY_BUFFER, data, size) {}

		void AddVertexAttribute(VertexAttributeType attribType, GLboolean normalized = GL_FALSE);

		GLuint GetStride() const { return m_Stride; }
		GLuint GetAttribCount() const { return m_AttribCount; }

		std::unordered_map<GLuint, VertexAttribute*> GetAttributes() { return m_VertexAttributes; }
	private:
		GLuint m_Stride = 0;
		GLuint m_AttribCount = 0;

		std::unordered_map<GLuint, VertexAttribute*> m_VertexAttributes = std::unordered_map<GLuint, VertexAttribute*>();
	};

	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer(void* data, GLuint size) : Buffer(GL_ELEMENT_ARRAY_BUFFER, data, size) {}
	};
}