#pragma once

#include "Event.h"

#include <sstream>

namespace miosGE {
	class MIOS_API KeyEvent : public Event {
	public:
		
		inline unsigned int GetKeyCode() const { return m_iKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			:m_iKeyCode(keycode) {}
		int m_iKeyCode;
	};

	class MIOS_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_iRepeatCount(repeatCount) {}

		inline unsigned int GetRepeatCount() const { return m_iRepeatCount; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_iKeyCode << "(" << m_iRepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_iRepeatCount;
	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_iKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_iKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}

