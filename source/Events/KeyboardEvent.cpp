#include "KeyboardEvent.h"

namespace Atum
{
namespace Events
{

KeyboardEvent::KeyboardEvent( unsigned int keyEntered, KeyboardEventType eventType, KeyboardModifier modifier, int x, int y )
	:m_keyEntered(keyEntered), 
	m_eventType(eventType),
	m_modifier(modifier),
	m_posX(x), 
	m_posY(y)
{}

KeyboardEvent::~KeyboardEvent()
{
}

unsigned char KeyboardEvent::GetKey() const
{
	if ( m_keyEntered <= 255 )
	{
		return (unsigned char)m_keyEntered;
	}
	else
	{
		return 0;
	}
}

int KeyboardEvent::GetSpecialKey() const
{
	if ( m_keyEntered > 255 )
	{
		return m_keyEntered;
	}
	else 
	{
		return KEY_NO_SPECIAL;
	}
}

}
}