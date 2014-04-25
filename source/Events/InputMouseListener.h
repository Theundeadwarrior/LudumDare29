
#ifndef _INPUTMOUSELISTENER_H
#define _INPUTMOUSELISTENER_H

#include "MouseEvent.h"

namespace Atum
{
namespace Events
{
	class InputMouseListener {

		public:
			InputMouseListener() {};
			virtual ~InputMouseListener() {} ;

			virtual void NotifyMouseClicked( const MouseEvent& event ) {};
			virtual void NotifyMouseMoved( const MouseEvent& event ) {};
	};

}
}

#endif  //_INPUTMOUSELISTENER_H
