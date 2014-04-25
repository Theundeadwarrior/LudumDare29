#include "MouseEvent.h"

namespace Atum
{
namespace Events
{

MouseEvent::MouseEvent( MouseEventType eventType, MouseClick clickType, MouseModifier modifier, int x, int y)
	:m_eventType(eventType),
	m_clickType(clickType), 
	m_modifier(modifier),
	m_posX(x), 
	m_posY(y)
{
}

MouseEvent::MouseEvent( int x, int y, MouseModifier modifier )
	:m_eventType( MOUSE_MOTION_ONLY ), m_posX(x), m_posY(y), m_clickType(NO_CLICK), m_modifier(modifier)
{
}

MouseEvent::~MouseEvent()
{
}


}
}