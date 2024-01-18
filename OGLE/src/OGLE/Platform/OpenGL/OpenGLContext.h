#pragma once

#include <OGLE/Renderer/GraphicsContext.h>

struct GLFWwindow;

namespace OGLE
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		~OpenGLContext() = default;

		void Init();
		void SwapBuffers();

		static Scope<OpenGLContext> Create(void* window);
	private:
		GLFWwindow* m_WindowHandle;

	};

	
}
