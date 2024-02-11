#include "gmpch.h"
#include "Window.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <fstream>

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

	// Function to compile a shader and check for errors
	GLuint CompileShader(const GLenum type, const GLchar* source) {
		const GLuint shader = glCreateShader(type);
	    glShaderSource(shader, 1, &source, nullptr);
	    glCompileShader(shader);

	    // Check for compile errors
	    int success;
	    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	    if (!success) {
		    char info_log[512];
		    glGetShaderInfoLog(shader, 512, nullptr, info_log);
	        std::cerr << "COMPILATION_FAILED\n" << info_log << std::endl;
	    }

	    return shader;
	}

	// Function to create a shader program from vertex and fragment shader sources
	GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
		// 1. retrieve the vertex/fragment source code from filePath
	    std::string vertexCode;
	    std::string fragmentCode;
	    std::ifstream vShaderFile;
	    std::ifstream fShaderFile;
	    // ensure ifstream objects can throw exceptions:
	    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	    try 
	    {
	        // open files
	        vShaderFile.open(vertexSource);
	        fShaderFile.open(fragmentSource);
	        std::stringstream vShaderStream, fShaderStream;
	        // read file's buffer contents into streams
	        vShaderStream << vShaderFile.rdbuf();
	        fShaderStream << fShaderFile.rdbuf();		
	        // close file handlers
	        vShaderFile.close();
	        fShaderFile.close();
	        // convert stream into string
	        vertexCode   = vShaderStream.str();
	        fragmentCode = fShaderStream.str();		
	    }
	    catch(std::ifstream::failure e)
	    {
	        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	    }
	    const char* vShaderCode = vertexCode.c_str();
	    const char* fShaderCode = fragmentCode.c_str();
	    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vShaderCode);
	    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fShaderCode);

	    // Link shaders
	    GLuint shaderProgram = glCreateProgram();
	    glAttachShader(shaderProgram, vertexShader);
	    glAttachShader(shaderProgram, fragmentShader);
	    glLinkProgram(shaderProgram);

	    // Check for linking errors
	    GLint success;
	    GLchar infoLog[512];
	    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	    if (!success) {
	        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	    }

	    // Delete the shaders as they're linked into our program now and no longer needed
	    glDeleteShader(vertexShader);
	    glDeleteShader(fragmentShader);

	    return shaderProgram;
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
		

		ShaderProgram = createShaderProgram("D:/data/Projects/eopGuiMaker/src/EopGuiMaker/OpenGL/vertex_shader.glsl",
			"D:/data/Projects/eopGuiMaker/src/EopGuiMaker/OpenGL/fragment_shader.glsl");
		float quadVertices[] = {
		    // positions   // flipped texCoords
		    -1.0f,  1.0f,  0.0f, 0.0f,
		    -1.0f, -1.0f,  0.0f, 1.0f,
		     1.0f, -1.0f,  1.0f, 1.0f,

		    -1.0f,  1.0f,  0.0f, 0.0f,
		     1.0f, -1.0f,  1.0f, 1.0f,
		     1.0f,  1.0f,  1.0f, 0.0f
		};
		unsigned int quadVBO;
		glGenVertexArrays(1, &Quads);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(Quads);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
		SetBackgroundImage("D:/data/Projects/EopGuiMaker/Resources/gameBackgroundStrat.png");

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

	void Window::SetBackgroundImage(const char* path)
	{
		Application::Get().texture = *Application::LoadImage(path, 1920, 1080);
		hasBackground = true;
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
