#ifndef GL_WINDOW_CLASS
#define GL_WINDOW_CLASS

#include <Core/Core.h>


static bool isInit = false;

class Window
{
public:
	Window();
	~Window();
private:
	GLFWwindow* m_WindowID;
};

#endif
