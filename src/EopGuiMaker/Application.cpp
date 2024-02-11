#include "gmpch.h"
#include "Application.h"

#include "ImGui/ImGuiLayer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <OpenGL/stb_image.h>

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

	
	GLuint* Application::LoadImage(const char* path, int width, int height, int channels, unsigned char* data)
	{
		unsigned char* bgData = stbi_load(path, &width, &height, &channels, 0);
		GLuint bgTexture;
		glGenTextures(1, &bgTexture);
		glBindTexture(GL_TEXTURE_2D, bgTexture);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Upload the image to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA : GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, bgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Free the image memory
		stbi_image_free(bgData);

		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		return &bgTexture;
	}

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
			m_Window->OnUpdate();

			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
			{
				(*--it)->OnUpdate();
			}
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

