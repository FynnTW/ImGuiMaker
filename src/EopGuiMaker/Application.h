#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "glad/glad.h"

namespace EopGuiMaker
{
	class GUIMAKER_API Application
	{
	public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& e);
		
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);

			static Application& Get() { return *m_Instance; }

			static GLuint* LoadImage(const char* path, int width, int height, int channels = 4, unsigned char* data = nullptr);

			GLuint texture;

			[[nodiscard]] Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* m_Instance;
	};

	Application* CreateApplication();


}

