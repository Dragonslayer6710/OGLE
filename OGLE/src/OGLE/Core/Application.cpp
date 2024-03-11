#include "oglepch.h"
#include "OGLE/Core/Application.h"

#include "OGLE/Scripting/ScriptEngine.h"

#include "OGLE/Input/Control.h"
#include "OGLE/Utils/PlatformUtils.h"

#include <stb_image.h>

namespace OGLE {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		stbi_set_flip_vertically_on_load(true);
		OGLE_PROFILE_FUNCTION();

		OGLE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name));
		m_Window->SetEventCallback(OGLE_BIND_EVENT_FN(Application::OnEvent));

		m_Renderer = new Renderer(m_Window->GetWidth(), m_Window->GetHeight());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		OGLE_PROFILE_FUNCTION();

		// TODO:Shutdown script engine
		// TODO:Shutdown Renderer
	}

	void Application::PushLayer(Layer* layer)
	{
		OGLE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		OGLE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::SubmitToMainThread(const std::function<void()>& function)
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		m_MainThreadQueue.emplace_back(function);
	}

	void Application::OnEvent(Event& e)
	{
		OGLE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(OGLE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(OGLE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		OGLE_PROFILE_FUNCTION();

		Timer timer;
		while (m_Running)
		{
			OGLE_PROFILE_SCOPE("RunLoop");

			ExecuteMainThreadQueue();
			double deltaTime = timer.GetDeltaTime();

			if (!minimized)
			{
				{
					OGLE_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(deltaTime);
				}

				m_ImGuiLayer->Begin();
				{
					OGLE_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		OGLE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;
		
		m_Renderer->OnWindowResize(e.GetWidth(), e.GetHeight());
		GetWindow().RecalculateCentrePos();
		return false;
	}

	void Application::ExecuteMainThreadQueue()
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		for (auto& func : m_MainThreadQueue)
			func();

		m_MainThreadQueue.clear();
	}

}