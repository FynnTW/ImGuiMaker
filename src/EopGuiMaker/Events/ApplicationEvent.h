#pragma once
#include "Event.h"

namespace EopGuiMaker {

#pragma region WindowResizeEvent
	/**
	 * \brief WindowResizeEvent is an event that is triggered when the window is resized.
	 */
	class GUIMAKER_API WindowResizeEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for the WindowResizeEvent
		 * \param width new width of the window
		 * \param height new height of the window
		 */
		WindowResizeEvent(const unsigned int width, const unsigned int height)
			: m_Width(width), m_Height(height) {}

		/**
		 * \brief Get the new width of the window
		 * \return the new width of the window
		 */
		inline unsigned int GetWidth() const { return m_Width; }

		/**
		 * \brief Get the new height of the window
		 * \return the new height of the window
		 */
		inline unsigned int GetHeight() const { return m_Height; }

		/**
		 * \brief String representation of the WindowResizeEvent
		 * \return String representation of the WindowResizeEvent
		 */
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};
#pragma endregion WindowResizeEvent

#pragma region WindowCloseEvent
	/**
	 * \brief WindowCloseEvent is an event that is triggered when the window is closed.
	 */
	class GUIMAKER_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
#pragma endregion WindowCloseEvent

#pragma region AppTickEvent
	/**
	 * \brief AppTickEvent is an event that is triggered when the application ticks.
	 */
	class GUIMAKER_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
#pragma endregion AppTickEvent

#pragma region AppUpdateEvent
	/**
	 * \brief AppTickEvent is an event that is triggered when the application updates.
	 */
	class GUIMAKER_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
#pragma endregion AppUpdateEvent

#pragma region AppRenderEvent
	/**
	 * \brief AppTickEvent is an event that is triggered when the application renders.
	 */
	class GUIMAKER_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
#pragma endregion AppRenderEvent

}