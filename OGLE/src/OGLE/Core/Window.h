#pragma once

#include "OGLE/Core/Base.h"
#include "OGLE/Events/Event.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <sstream>

namespace OGLE {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "OGLE",
			uint32_t width = OGLE_DEF_WIDTH,
			uint32_t height = OGLE_DEF_HEIGHT)
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

		unsigned int GetWidth() const { return m_Data.Width; }
		unsigned int GetHeight() const { return m_Data.Height; }

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
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
