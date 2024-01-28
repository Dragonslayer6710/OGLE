#include "oglepch.h"
#include "OGLE/Display/Window.h"

#include "OGLE/Input/Input.h"

#include "OGLE/Event/ApplicationEvent.h"
#include "OGLE/Event/MouseEvent.h"
#include "OGLE/Event/KeyEvent.h"

#include "OGLE/Display/Renderer/Renderer.h"

#include "OGLE/OpenGL/OpenGLContext.h"

namespace OGLE {

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef OGLE_PLATFORM_WINDOWS
		return CreateScope<Window>(props);
#else
		OGLE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

	void Window::RecalculateCentrePos()
	{
		m_CentrePos = glm::vec2(GetWidth() / 2, GetHeight() / 2);
	}

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		OGLE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(const WindowProps& props)
	{
		OGLE_PROFILE_FUNCTION();

		Init(props);
	}

	Window::~Window()
	{
		OGLE_PROFILE_FUNCTION();

		Shutdown();
	}

	void Window::Init(const WindowProps& props)
	{
		OGLE_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		RecalculateCentrePos();
		OGLE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (s_GLFWWindowCount == 0)
		{
			OGLE_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			OGLE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		{
			OGLE_PROFILE_SCOPE("glfwCreateWindow");
#if defined(OGLE_DEBUG)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = OpenGLContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			}
		);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.EventCallback(event);
					break;
				}
				}
			}
		);
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			}
		);
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			}
		);
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((const float)xOffset, (const float)yOffset);
				data.EventCallback(event);
			}
		);
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((const float)xPos, (const float)yPos);
				data.EventCallback(event);
			}
		);
	}

	void Window::Shutdown()
	{
		OGLE_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		OGLE_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}


	void Window::SetVSync(bool enabled)
	{
		OGLE_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	void Window::HideCursor()
	{
		if (!m_CursorHidden) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_CursorHidden = true;
		}
	}

	void Window::RevealCursor()
	{
		if (m_CursorHidden) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			CentreCursor();
			m_CursorHidden = false;
		}
	}

	void Window::CentreCursor()
	{		
		glfwSetCursorPos(m_Window, m_CentrePos.x, m_CentrePos.y);
	}

}