#include "oglepch.h"
#include "OGLE/OpenGL/OpenGLContext.h"

namespace OGLE
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		OGLE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		OGLE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OGLE_CORE_ASSERT(status, "Failed to initialize Glad!");

		OGLE_CORE_INFO("OpenGL Info:");
		OGLE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		OGLE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		OGLE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		OGLE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "OGLE requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		OGLE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

	Scope<OpenGLContext> OpenGLContext::Create(void* window)
	{
		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}
}