#pragma once

#include "Event.h"

namespace EopGuiMaker {

#pragma region MouseMovedEvent
	/**
	 * \brief MouseMovedEvent is an event that is triggered when the mouse is moved.
	 */
	class GUIMAKER_API MouseMovedEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for the MouseMovedEvent
		 * \param x x position of the mouse
		 * \param y y position of the mouse
		 */
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		/**
		 * \brief Get the x position of the mouse
		 * \return x position of the mouse
		 */
		[[nodiscard]] inline float GetX() const { return m_MouseX; }
		/**
		 * \brief Get the y position of the mouse
		 * \return y position of the mouse
		 */
		[[nodiscard]] inline float GetY() const { return m_MouseY; }

		/**
		 * \brief Get a string representation of the MouseMovedEvent
		 * \return string representation of the MouseMovedEvent
		 */
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		/**
		 *Event type of the MouseMovedEvent
		 */
		EVENT_CLASS_TYPE(MouseMoved)
		/**
		 *Event categories of the MouseMovedEvent
		 */
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};
#pragma endregion MouseMovedEvent

#pragma region MouseScrolledEvent
	/**
	 * \brief MouseMovedEvent is an event that is triggered when the mouse is scrolled.
	 */
	class GUIMAKER_API MouseScrolledEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for the MouseScrolledEvent
		 * \param x_offset x offset of the scroll
		 * \param y_offset y offset of the scroll
		 */
		MouseScrolledEvent(const float x_offset, const float y_offset)
			: m_XOffset(x_offset), m_YOffset(y_offset) {}

		/**
		 * \brief Get the x offset of the mouse
		 * \return x offset of the mouse
		 */
		[[nodiscard]] inline float GetXOffset() const { return m_XOffset; }
		/**
		 * \brief Get the y offset of the mouse
		 * \return y offset of the mouse
		 */
		[[nodiscard]] inline float GetYOffset() const { return m_YOffset; }
		
		/**
		 * \brief Get a string representation of the MouseScrolledEvent
		 * \return string representation of the MouseScrolledEvent
		 */
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
		
		/**
		 *Event type of the MouseScrolledEvent
		 */
		EVENT_CLASS_TYPE(MouseScrolled)
		/**
		 *Event categories of the MouseScrolledEvent
		 */
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};
#pragma endregion MouseScrolledEvent

#pragma region MouseButtonEvent
	/**
	 * \brief MouseButtonEvent is an event that is triggered when something happens to a mouse button.
	 * You can't directly create an instance of this class, you have to use MouseButtonPressedEvent or MouseButtonReleasedEvent
	 */
	class GUIMAKER_API MouseButtonEvent : public Event
	{
	public:
		/**
		 * \brief Get the mouse button used.
		 * \return the mouse button used.
		 */
		[[nodiscard]] inline int GetMouseButton() const { return m_Button; }

		/**
		 *Event categories of the MouseButtonEvent
		 */
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		/**
		 * \brief Constructor for the MouseButtonEvent
		 * \param button button that was clicked
		 */
		explicit MouseButtonEvent(const int button)
			: m_Button(button) {}

		int m_Button;
	};
#pragma endregion MouseButtonEvent

#pragma region MouseButtonPressedEvent
	/**
	 * \brief MouseButtonPressedEvent is an event that is triggered when a mouse button is pressed.
	 */
	class GUIMAKER_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * \brief Constructor for the MouseButtonPressedEvent
		 * \param button button that was clicked
		 */
		explicit MouseButtonPressedEvent(const int button)
			: MouseButtonEvent(button) {}
		
		/**
		 * \brief Get a string representation of the MouseButtonPressedEvent
		 * \return string representation of the MouseButtonPressedEvent
		 */
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		
		/**
		 *Event type of the MouseMovedEvent event
		 *No categories as they are already in the MouseButtonEvent
		 */
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
#pragma endregion MouseButtonPressedEvent

#pragma region MouseButtonReleasedEvent
	/**
	 * \brief MouseButtonReleasedEvent is an event that is triggered when a mouse button is released.
	 */
	class GUIMAKER_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * \brief Constructor for the MouseButtonReleasedEvent
		 * \param button button that was clicked
		 */
		explicit MouseButtonReleasedEvent(const int button)
			: MouseButtonEvent(button) {}
		
		/**
		 * \brief Get a string representation of the MouseButtonReleasedEvent
		 * \return string representation of the MouseButtonReleasedEvent
		 */
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		
		/**
		 *Event type of the MouseButtonReleased event
		 *No categories as they are already in the MouseButtonEvent
		 */
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
#pragma endregion MouseButtonReleasedEvent

}