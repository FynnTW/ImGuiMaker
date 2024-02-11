#include "gmpch.h"
#include "Application.h"

#include "ImGui/ImGuiLayer.h"

namespace EopGuiMaker
{

#define BIND_EVENT_FN(x) [this](auto& event) {return x(event);}

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		GUIMAKER_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		//Here is sets onEvent as the function that gets fired when an event is triggered
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	= default;

	void Application::OnEvent(Event& e)
	{
		//creates an EventDispatcher object with the event e
		EventDispatcher dispatcher(e);
		//If the event is a window close event, it will call the OnWindowClose function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	[[noreturn]] void Application::Run()
	{
		while (m_Running)
		{
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
			{
				(*--it)->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}

