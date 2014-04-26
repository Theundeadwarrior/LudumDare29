/******************************************
 ---- Event Manager ---- 

 Voici les combinaisons de touches qui ne fonctionnent pas.

- CTRL + un chiffre: Seul l'event de KEY_RELEASED est envoyé.

- Deux modifiers activés en même temps: Par exemple, si SHIFT + CTRL sont activés, 
  un caractère random est lancé en tant que KEY_RELEASED.

- Les touches Fn ne sont pas activées, si un jour arrive où ces touches vont être
  nécessaires, alors il faut le coder!


  ---- Lien avec le UiManager ----

  Étant donné que AntTweakBar (qui génère les fenêtres UI en OpenGL) se connecte
  aux fonctions de callback de GLUT, il y a un petit conflit car l'EventManager
  se connecte lui aussi à GLUT. Ainsi, EventManager appelle le UiManager pour 
  savoir si l'event provenant de GLUT a été attrapé par le UI.

*******************************************/

#include "UserInterface/Ui/UiManager.h"
#include "GL/freeglut.h"

#include "EventManager.h"
#include "InputMouseListener.h"
#include "InputKeyboardListener.h"

namespace Atum
{
namespace Events
{


EventManager::EventManager()
{
	glutMouseFunc(EventManager::InputMouseGLUT);
	glutMotionFunc(EventManager::InputMouseMotionGLUT);
	glutPassiveMotionFunc(EventManager::InputMouseMotionGLUT);
	glutKeyboardFunc(EventManager::InputKeyboardPressedGLUT);
	glutKeyboardUpFunc(EventManager::InputKeyboardReleasedGLUT);
	glutSpecialFunc(EventManager::InputSpecialKeyboardPressedGLUT);
	glutSpecialUpFunc(EventManager::InputSpecialKeyboardReleasedGLUT);

	glutIgnoreKeyRepeat(true);
}

EventManager::~EventManager()
{
}

EventManager& EventManager::GetInstance()
{
	static EventManager instance;
	return instance;
}


void EventManager::RegisterMouseListener(InputMouseListener* listener) 
{
	m_inputMouseList.push_back(listener);
}

void EventManager::RegisterKeyboardListener(InputKeyboardListener* listener) 
{
	m_inputKeyboardList.push_back(listener);
}

void EventManager::UnregisterMouseListener(InputMouseListener* listener) 
{
	m_inputMouseList.remove(listener);
}

void EventManager::UnregisterKeyboardListener(InputKeyboardListener* listener) 
{
	m_inputKeyboardList.remove(listener);
}

void EventManager::UpdateMouseListener( const MouseEvent& event ) 
{
	std::list<InputMouseListener*>::iterator iter( m_inputMouseList.begin() );
	for ( ; iter != m_inputMouseList.end(); iter++)
	{
		if ( *iter && event.GetType() == MOUSE_MOTION_ONLY ) 
		{
			(*iter)->NotifyMouseMoved(event);
		}
		else if ( *iter ) //click!
		{
			(*iter)->NotifyMouseClicked(event);
		}
	}
}

void EventManager::UpdateKeyboardListener( const KeyboardEvent& event ) 
{
	std::list<InputKeyboardListener*>::iterator iter( m_inputKeyboardList.begin() );
	for ( ; iter != m_inputKeyboardList.end(); iter++)
	{
		if ( *iter ) //click!
		{
			(*iter)->NotifyKeyPressed(event);
		}
	}
}

void EventManager::InputMouseGLUT( int button, int state, int x, int y )
{
	//if ( ! UserInterface::UiManager::CallbackMouseTw(button, state, x,y) ) //event was not handled by AntTweakBar
	{
		MouseClick clickType = NO_CLICK;
		MouseEventType eventType = MOUSE_MOTION_ONLY;
		MouseModifier modifierType ( CreateMouseModifier() );

		if ( state == GLUT_UP )
		{
			eventType = MOUSE_UP;
		}
		else if ( state == GLUT_DOWN )
		{
			eventType = MOUSE_DOWN;
		}

		if ( button == GLUT_LEFT_BUTTON )
		{
			clickType = LEFT_CLICK;
		}
		else if ( button == GLUT_RIGHT_BUTTON )
		{
			clickType = RIGHT_CLICK;
		}
		else if ( button == GLUT_MIDDLE_BUTTON )
		{
			clickType = MIDDLE_CLICK;
		}
		else if ( button == 3)
		{
			eventType = SCROLL_UP;
			if (state == GLUT_UP) return;
		}
		else if ( button == 4)
		{
			eventType = SCROLL_DOWN;
			if (state == GLUT_UP) return;
		}

		MouseEvent mouseEvent(eventType, clickType, modifierType, x, y);
		EventManager::GetInstance().UpdateMouseListener( mouseEvent );
	}
}

void  EventManager::InputMouseMotionGLUT( int x, int y )
{
	UserInterface::UiManager::CallbackMouseMotionTw(x,y);
		
	MouseModifier modifier ( CreateMouseModifier() );
	MouseEvent mouseEvent( x,y, modifier );
	EventManager::GetInstance().UpdateMouseListener( mouseEvent );
}

void EventManager::InputKeyboardPressedGLUT( unsigned char key, int x , int y )
{
	//if ( ! UserInterface::UiManager::CallbackKeyboardInputTw(key,x,y) ) //event was not handled by AntTweakBar
	{
		KeyboardModifier modifier ( CreateKeyboardModifier() );
		KeyboardEventType eventType = KEY_PRESSED;

		//special case for the CTRL modifier
		if ( key > 0 && key < KEY_LUT_LENGTH+1 && modifier == KEYBOARD_ACTIVE_CTRL )
		{
			key = CTRL_KEY_LUT[key-1];
		}

		KeyboardEvent keyEvent( key, eventType, modifier, x, y );
		EventManager::GetInstance().UpdateKeyboardListener(keyEvent);
	}
}

void EventManager::InputKeyboardReleasedGLUT( unsigned char key, int x , int y )
{
	KeyboardModifier modifier ( KEYBOARD_NO_MODIFIER );
	KeyboardEventType eventType = KEY_RELEASED;

	KeyboardModifier currentModifier( CreateKeyboardModifier() );
	//sad case for when CTRL, ALT or SHIFT are released
	if ( key < EVENT_MANAGER_ALT_KEY_CODE && key > EVENT_MANAGER_CTRL_KEY_CODE && currentModifier == KEYBOARD_NO_MODIFIER )
		return;

	//special case for the CTRL modifier
	if ( key > 0 && key < KEY_LUT_LENGTH+1 && currentModifier == KEYBOARD_ACTIVE_CTRL )
	{
		key = CTRL_KEY_LUT[key-1];
	}

	KeyboardEvent keyEvent( key, eventType, modifier, x, y );
	EventManager::GetInstance().UpdateKeyboardListener(keyEvent);
}

void EventManager::InputSpecialKeyboardPressedGLUT( int key, int x , int y )
{
	//if ( ! UserInterface::UiManager::CallbackKeyboardSpecialTw(key,x,y) ) //event was not handled by AntTweakBar
	{
		KeyboardSpecialKey specialKey( CreateSpecialKeyboardKey(key) );

		if ( specialKey != KEY_NO_SPECIAL )
		{
			KeyboardEventType eventType( KEY_PRESSED );
			KeyboardModifier modifier ( CreateKeyboardModifier() );
			KeyboardEvent keyEvent( specialKey, eventType, modifier,  x, y);
			EventManager::GetInstance().UpdateKeyboardListener(keyEvent);
		}
	}
}

void EventManager::InputSpecialKeyboardReleasedGLUT( int key, int x , int y )
{
	KeyboardSpecialKey specialKey( CreateSpecialKeyboardKey(key) );

	if ( specialKey != KEY_NO_SPECIAL )
	{
		KeyboardEventType eventType( KEY_RELEASED );
		KeyboardModifier modifier ( KEYBOARD_NO_MODIFIER );
		KeyboardEvent keyEvent( specialKey, eventType, modifier,  x, y);
		EventManager::GetInstance().UpdateKeyboardListener(keyEvent);
	}
}

MouseModifier EventManager::CreateMouseModifier()
{
	MouseModifier modifier = MOUSE_NO_MODIFIER;
	int glutModifier = glutGetModifiers();

	if ( glutModifier == GLUT_ACTIVE_SHIFT )
	{
		modifier = MOUSE_ACTIVE_SHIFT;
	}
	else if ( glutModifier == GLUT_ACTIVE_CTRL )
	{
		modifier = MOUSE_ACTIVE_CTRL;
	}
	else if ( glutModifier == GLUT_ACTIVE_ALT )
	{
		modifier = MOUSE_ACTIVE_ALT;
	}
	return modifier;
}

KeyboardModifier EventManager::CreateKeyboardModifier()
{
	return (KeyboardModifier)CreateMouseModifier();
}

KeyboardSpecialKey EventManager::CreateSpecialKeyboardKey( int key )
{
	KeyboardSpecialKey specialKey = KEY_NO_SPECIAL;

	if ( key == GLUT_KEY_UP )
	{
		specialKey = KEY_UP;
	}
	else if ( key == GLUT_KEY_DOWN )
	{
		specialKey = KEY_DOWN;
	}
	else if ( key == GLUT_KEY_RIGHT )
	{
		specialKey = KEY_RIGHT;
	}
	else if ( key == GLUT_KEY_LEFT )
	{
		specialKey = KEY_LEFT;
	}

	return specialKey;
}

}
}