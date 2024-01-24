#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifndef GL_LOG_CALL
#define GL_LOG_CALL
static void GLClearError() {
	while (glGetError());
}

#define GLCall(x) GLClearError();\
	x;\
	OGLE_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" <<  function <<
			" " << file << ":"<< line << std::endl;
		return false;
	}
	return true;
}
#endif


namespace OGLE
{
	class OpenGLContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init();
		void SwapBuffers();
		static Scope<OpenGLContext> Create(void* window);
	private:
		GLFWwindow* m_WindowHandle;
	};

	
}
