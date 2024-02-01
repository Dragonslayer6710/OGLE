#pragma once
#include "OGLE/OGL/OpenGL.h"


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
