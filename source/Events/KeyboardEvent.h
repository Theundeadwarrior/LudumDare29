
#ifndef _KEYBOARDEVENT_H
#define _KEYBOARDEVENT_H

namespace Atum
{
namespace Events
{
	const unsigned char CTRL_KEY_LUT[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	const unsigned char KEY_LUT_LENGTH = 26;

	enum KeyboardEventType{
		KEY_PRESSED = 0,
		KEY_RELEASED,
	};

	enum KeyboardSpecialKey{
		KEY_NO_SPECIAL = 256,
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT
	};

	enum KeyboardModifier{
		KEYBOARD_NO_MODIFIER = 0,
		KEYBOARD_ACTIVE_SHIFT,
		KEYBOARD_ACTIVE_ALT,
		KEYBOARD_ACTIVE_CTRL
	};

	class KeyboardEvent {
		public:
			KeyboardEvent(unsigned int keyEntered, KeyboardEventType eventType, KeyboardModifier modifier, int x, int y);
			~KeyboardEvent();
			unsigned char GetKey() const;
			int GetSpecialKey() const;
			KeyboardEventType GetEventType() const { return m_eventType; }
			int GetXPosition() const { return m_posX; }
			int GetYPosition() const { return m_posY; }
			KeyboardModifier GetModifier() const { return m_modifier; }

		private:
			unsigned int m_keyEntered;
			KeyboardEventType m_eventType;
			KeyboardModifier m_modifier;
			int m_posX, m_posY;
	};

}
}

#endif  //_KEYBOARDEVENT_H
