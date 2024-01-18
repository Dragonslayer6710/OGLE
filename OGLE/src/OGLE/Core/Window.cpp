#include "oglepch.h"
#include "Window.h"

Window::Window()
{
	if (!isInit) {
		isInit = glfwInit();
		if (!isInit)
			throw std::runtime_error("GLFW Failed To initialize!");
	}
}

Window::~Window()
{

}
