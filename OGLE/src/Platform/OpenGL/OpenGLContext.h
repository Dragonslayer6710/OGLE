#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
