#include "oglepch.h"
#include "OGLE/Core/Window.h"

#ifdef OGLE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace OGLE
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef OGLE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		OGLE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}