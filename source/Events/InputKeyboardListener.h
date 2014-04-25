
#ifndef _INPUTKEYBOARDLISTENER_H
#define _INPUTKEYBOARDLISTENER_H

#include "KeyboardEvent.h"

namespace Atum
{
namespace Events
{

	class InputKeyboardListener {

		public:
			InputKeyboardListener() {};
			~InputKeyboardListener() {};

			virtual void NotifyKeyPressed( const KeyboardEvent& event) {};
	};

}
}

#endif  //_INPUTKEYBOARDLISTENER_H
