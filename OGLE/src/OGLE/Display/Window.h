#pragma once

#include "OGLE/Core/Base.h"
#include "OGLE/Event/Event.h"
#include "OGLE/OpenGL/OpenGLContext.h"

#include <sstream>

namespace OGLE {

	struct WindowProps
	{
		std::string Title;
		GLsizei Width;
		GLsizei Height;

		WindowProps(const std::string& title = "OGLE",
			GLsizei width = OGLE_DEF_WIDTH,
			GLsizei height = OGLE_DEF_HEIGHT)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props);
		virtual ~Window();

		void OnUpdate();

		GLsizei GetWidth() const { return m_Data.Width; }
		GLsizei GetHeight() const { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		virtual void* GetNativeWindow() const { return m_Window; }

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<OpenGLContext> m_Context;

		struct WindowData
		{
			std::string Title;
			GLsizei Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
