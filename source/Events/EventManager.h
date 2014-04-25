
#ifndef EVENTS_EVENTMANAGER_H
#define EVENTS_EVENTMANAGER_H

#include <list>

#include "InputMouseListener.h"
#include "InputKeyboardListener.h"

#define EVENT_MANAGER_CTRL_KEY_CODE 15
#define EVENT_MANAGER_ALT_KEY_CODE 19

namespace Atum
{
namespace Events
{
	class EventManager {

		public:
			~EventManager();
			static EventManager& GetInstance();

			void RegisterMouseListener(InputMouseListener* listener);
			void RegisterKeyboardListener(InputKeyboardListener* listener);
			void UnregisterMouseListener(InputMouseListener* listener);
			void UnregisterKeyboardListener(InputKeyboardListener* listener);

			//Connect to GLUT callback functions
			static void InputMouseGLUT (int button, int state, int x, int y);
			static void InputMouseMotionGLUT (int x, int y);
			static void InputKeyboardPressedGLUT (unsigned char key, int x , int y);
			static void InputSpecialKeyboardPressedGLUT (int key, int x , int y);
			static void InputKeyboardReleasedGLUT (unsigned char key, int x , int y);
			static void InputSpecialKeyboardReleasedGLUT (int key, int x , int y);

		private:
			EventManager();
			EventManager(EventManager const&);   // Don't Implement
			void operator=(EventManager const&); // Don't implement

			static KeyboardSpecialKey CreateSpecialKeyboardKey(int key);
			static KeyboardModifier CreateKeyboardModifier();
			static MouseModifier CreateMouseModifier();

			void UpdateMouseListener( const MouseEvent& event );
			void UpdateKeyboardListener( const KeyboardEvent& event );

			std::list<InputMouseListener*> m_inputMouseList;
			std::list<InputKeyboardListener*> m_inputKeyboardList;
	};

}
}

#endif  //EVENTS_EVENTMANAGER_H
