#pragma once

#include "gmpch.h"

#include "Core.h"
#include "Events/Event.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace EopGuiMaker {

#pragma region WindowProps
	/**
	 * \brief Structure to hold window properties
	 */
	struct WindowProps
	{
		// Window title
		std::string Title;
		// Window width
		unsigned int Width;
		// Window height
		unsigned int Height;

		/**
		 * \brief Constructor
		 * \param title Title of the window
		 * \param width Width of the window
		 * \param height Height of the window
		 */
		explicit WindowProps(std::string title = "EOP GUI Maker", const unsigned int width = 1920, const unsigned int height = 1080)
			: Title(std::move(title)), Width(width), Height(height)
		{

		}
	};
#pragma endregion WindowProps

#pragma region Window
	/**
	 * \brief Interface representing a desktop system based Window
	 */
	class GUIMAKER_API Window
	{
	public:
		// Event callback function. This function will be called when an event occurs.
		using EventCallbackFn = std::function<void(Event&)>;

		/**
		 * \brief Constructor
		 * \param props Window properties
		 */
		explicit Window(const WindowProps& props);

		// Destructor
		virtual ~Window();

		// Update function
		void OnUpdate() const;

		/**
		 * \brief Get the width of the window
		 * \return Width of the window
		 */
		[[nodiscard]] unsigned int GetWidth() const { return m_Data.Width; }
		/**
		 * \brief Get the height of the window
		 * \return Height of the window
		 */
		[[nodiscard]] unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		/**
		 * \brief brief Set the event callback function
		 * \param callback  Event callback function
		 */
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		/**
		 * \brief Set if the window is VSync enabled
		 * \param enabled true to enable VSync, false to disable
		 */
		void SetVSync(bool enabled);
		/**
		 * \brief Check if the window is VSync enabled
		 * \return True if VSync is enabled, false if not
		 */
		[[nodiscard]] bool IsVSync() const;

		[[nodiscard]] GLFWwindow* GetNativeWindow() const { return m_Window; }

		bool hasBackground = false;

		void SetBackgroundImage(const char* path);

		GLuint ShaderProgram;

		/**
		 * \brief Create a window
		 * \param props Window properties
		 * \return Window pointer
		 */
		static Window* Create(const WindowProps& props = WindowProps());

		private:
			virtual void Init(const WindowProps& props);
			virtual void Shutdown();
			GLFWwindow* m_Window{};
			unsigned int m_Quads;
			struct WindowData
			{
				std::string Title;
				unsigned int Width{}, Height{};
				bool VSync{};

				EventCallbackFn EventCallback;
			};

			WindowData m_Data;

	};
#pragma endregion Window

}
