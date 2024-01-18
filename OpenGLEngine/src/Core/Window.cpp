#include "Window.h"

Window::Window()
{
	if (!isInit) {
		isInit = glfwInit();
		if (!isInit)
			throw Exception("GLFW Failed To initialize!");
	}
}

Window::~Window()
{

}
