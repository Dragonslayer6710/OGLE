#include "oglepch.h"
#include <OGLE/Renderer/GraphicsContext.h>

#include <OGLE/Renderer/Renderer.h>
#include <OGLE/Platform//OpenGL/OpenGLContext.h>

namespace OGLE{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}
}
