#include "gmpch.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "glad/glad.h"

namespace EopGuiMaker
{
	
	static bool S_GLFW_INITIALIZED = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new Window(props);
	}

	Window::Window(const WindowProps& props)
	{
		Window::Init(props);
	}

	Window::~Window()
	{
		Window::Shutdown();
	}

	void Window::Shutdown()
	{
		//glfwDestroyWindow(m_Window);
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GUIMAKER_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!S_GLFW_INITIALIZED)
		{
			int success = glfwInit();
			GUIMAKER_CORE_ASSERT(success, "Could not intialize GLFW!");

			S_GLFW_INITIALIZED = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		GUIMAKER_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			Width = width;
			Height = height;

			WindowResizeEvent event(width, height);
			EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, const int key, [[maybe_unused]] const int scan_code, const int action, const int mods)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						EventCallback(event);
						break;
					}
				case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						EventCallback(event);
						break;
					}
				default: ;
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, const int button, const int action, [[maybe_unused]] const int mods)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					EventCallback(event);
					break;
				}
				default: ;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const double x_offset, const double y_offset)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(static_cast<float>(x_offset), static_cast<float>(y_offset));
			EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const double x_pos, const double y_pos)
		{
			auto& [Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(x_pos), static_cast<float>(y_pos));
			EventCallback(event);
		});
	}

	void Window::OnUpdate() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(const bool enabled)
	{
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

}
