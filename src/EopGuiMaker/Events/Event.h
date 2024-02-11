#pragma once

#include "Core.h"

namespace EopGuiMaker
{
#pragma region Enums
	/**
	 * Enum of different event types.
	 */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * Enum of different event categories.
	 *
	 * For example: application, input, keyboard, mouse, mouse button.
	 * They are stored as bit flags. An event can be in multiple categories.
	 */
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
#pragma endregion Enums

#pragma region Macros
	/*
	* Here are macros to get the type of an event.
	* There are virtual functions that can be overridden by derived classes.
	*/
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
	
	/*
	* Here are macros to get the category of an event.
	* It is a virtual function that can be overridden by derived classes.
	*/
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
#pragma endregion Macros

#pragma region Event Class
	/**
	 * Base Event class.
	 */
	class GUIMAKER_API Event
	{

#pragma region public members
	public:

		bool Handled = false;

		//Pure virtual functions. They must be overridden by derived classes. It makes no sense to call them without using return, so they are marked as [[nodiscard]].
		/**
		 * \brief Get the type of the event.
		 * \return part of the enum EventType.
		 */
		[[nodiscard]] virtual EventType GetEventType() const = 0;
		/**
		 * \brief Get the string name of the event.
		 * \return name of the event.
		 */
		[[nodiscard]] virtual const char* GetName() const = 0;
		/**
		 * \brief Get the event categories the event is in.
		 * \return bitfield with the flags set. Use the enum EventCategory to check the flags.
		 */
		[[nodiscard]] virtual int GetCategoryFlags() const = 0;

		/**
		 * \brief Converts the event to a string representation.
		 * \return name of the event.
		 */
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }
		/**
		 * Returns true if the event is in the category.
		 * It is a virtual function. It can be overridden by derived classes.
		 * It is implemented in the base class.
		 * It is marked nodiscard because it makes no sense to call it without using return.
		 */
		[[nodiscard]] bool IsInCategory(const EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}
#pragma endregion public members

#pragma region protected members
	protected:
		bool m_Handled = false;
#pragma endregion protected members
	};
#pragma endregion Event Class

#pragma region EventDispatcher Class
	/**
	 * \brief EventDispatcher class.
	 */
	class EventDispatcher
	{
		// EventFn is a template alias for a function that takes a reference to a type T and returns a bool.
		template<typename T> using EventFn = std::function<bool(T&)>;

#pragma region public members
	public:
		/**
		 * \brief Constructor.
		 * \param event Reference to an event. 
		 */
		explicit EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		/**
		 * \brief Dispatches the event.
		 * \tparam T Class of the event.
		 * \param func function that takes a reference to a type T and returns a bool.
		 * \return true if the event is dispatched, has to be same type as the event type of the dispatcher.
		 */
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*static_cast<T*>(&m_Event));
				return true;
			}
			return false;
		}
#pragma endregion public members

#pragma region private members
	private:
		Event& m_Event;
#pragma endregion private members
	};
#pragma endregion EventDispatcher Class

	/**
	 * \brief Overload of the << operator for the Event class.
	 * \param os stream to write to.
	 * \param e event to write.
	 * \return written stream.
	 */
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}



