
#ifndef _MOUSEEVENT_H
#define _MOUSEEVENT_H

namespace Atum
{
namespace Events
{

	enum MouseEventType {
		MOUSE_MOTION_ONLY = 0,
		MOUSE_UP,
		MOUSE_DOWN,
		SCROLL_UP,
		SCROLL_DOWN
	};

	enum MouseClick{
		NO_CLICK = 0,
		LEFT_CLICK,
		RIGHT_CLICK,
		MIDDLE_CLICK 
	};

	enum MouseModifier{
		MOUSE_NO_MODIFIER = 0,
		MOUSE_ACTIVE_SHIFT,
		MOUSE_ACTIVE_ALT,
		MOUSE_ACTIVE_CTRL
	};

	class MouseEvent {
		public:
			MouseEvent(MouseEventType eventType, MouseClick clickType, MouseModifier modifier, int x, int y);
			MouseEvent(int x, int y, MouseModifier modifier);
			~MouseEvent();

			MouseEventType GetType() const {return m_eventType;}
			int GetXPosition() const {return m_posX;}
			int GetYPosition() const {return m_posY;}
			MouseClick GetClickType() const {return m_clickType;}
			MouseModifier GetModifier() const { return m_modifier; }

		private:
			MouseEventType m_eventType;
			MouseClick m_clickType;
			MouseModifier m_modifier;
			int m_posX, m_posY;
	};

}
}

#endif  //_MOUSEEVENT_H
