#pragma once

#include "OGLE/Core/Base.h"

#include "OGLE/Event/ApplicationEvent.h"
#include "OGLE/Event/MouseEvent.h"
#include "OGLE/Event/KeyEvent.h"

#include "OGLE/Display/Renderer/Renderer.h"

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

		glm::vec2 GetCentre() const { return glm::vec2(m_Data.Width / 2.0f, m_Data.Height / 2.0f); }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		virtual void* GetNativeWindow() const { return m_Window; }

		void RecalculateCentrePos();

		void CentreCursor();

		void HideCursor();

		void RevealCursor();

		bool IsCursorHidden();

		void SetImGuiLayerBlock(bool status) { m_ImGuiLayerBlock = status; };

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
		bool m_CursorHidden = false;
		bool m_ImGuiLayerBlock = false;
		glm::vec2 m_CentrePos;
	};

}
