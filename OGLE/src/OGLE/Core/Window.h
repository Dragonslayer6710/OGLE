#ifndef GL_WINDOW_CLASS
#define GL_WINDOW_CLASS

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
