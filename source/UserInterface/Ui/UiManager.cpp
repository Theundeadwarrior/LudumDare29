#include "UiManager.h"
#include <iostream>

#include "LowLevelGraphics/WindowManager/WindowManager.h"

#include "SceneManager/Objects/Object.h"
#include "SceneManager/SceneManager.h"

#include "Events/EventManager.h"


namespace Atum
{
namespace UserInterface
{

bool UiManager::m_isLeftButtonDown = false;
UiPropertyGrid UiManager::m_propertyGrid("Property Grid");
ComponentSelector UiManager::m_componentSelector;
UiPanel UiManager::m_globalPanel("Settings");

bool UiManager::m_isEventEnabled = false;
bool UiManager::m_isSelectionEnabled = false;
bool UiManager::m_isPanelEnabled = false;
bool UiManager::m_isPropertyGridEnabled = false;

UiManager::UiManager()
{
}

UiManager::~UiManager()
{
	DisableCompleteUi();
}

void UiManager::WindowResized( int width, int height )
{
	// Send the new window size to AntTweakBar
	TwWindowSize(width, height);
}

UiManager& UiManager::GetInstance()
{
	static UiManager instance; // Guaranteed to be destroyed.
	return instance;
}

void UiManager::DrawPanels()
{
	if ( m_isPanelEnabled )
		TwDraw();
}

void UiManager::EnableCompleteUi()
{
	SetCompleteUiState(true);
}

void UiManager::DisableCompleteUi()
{
	SetCompleteUiState(false);
}

void UiManager::SetCompleteUiState( bool state )
{
	SetEventsState(state);
	SetObjectSelectionState(state);
	SetPanelsState(state);
	SetPropertyGridState(state);
}

void UiManager::SetEventsState( bool state )
{
	if( !m_isEventEnabled && state )
	{
		//Connect to events
		Events::EventManager::GetInstance().RegisterMouseListener(this);
		Events::EventManager::GetInstance().RegisterKeyboardListener(this);
		m_isEventEnabled = true;
	}
	else if ( m_isEventEnabled && !state )
	{
		SetObjectSelectionState(false);
		Events::EventManager::GetInstance().UnregisterKeyboardListener(this);
		Events::EventManager::GetInstance().UnregisterMouseListener(this);
		m_isEventEnabled = false;
	}
}

void UiManager::SetPanelsState( bool state )
{
	if ( !m_isPanelEnabled && state ) //not enabled
	{
		InitTweakBar();
		InitGlobalPanel();
		m_isPanelEnabled = true;
	}
	else if ( m_isPanelEnabled && !state )
	{
		SetPropertyGridState(false); //propertyGrid is a panel too!
		DeleteTweakBar();
		m_isPanelEnabled = false;
	}
}

void UiManager::SetObjectSelectionState( bool state )
{
	if ( !m_isSelectionEnabled && state ) //not enabled
	{
		m_isSelectionEnabled = true;
	}
	else if ( m_isSelectionEnabled && !state )
	{
		m_componentSelector.ClearSelection();
		m_isSelectionEnabled = false;
	}
}

void UiManager::SetPropertyGridState( bool state )
{
	if ( !m_isPropertyGridEnabled && state ) //not enabled
	{
		SetPanelsState(true);
		m_propertyGrid.Init();
		m_isPropertyGridEnabled = true;
	}
	else if ( m_isPropertyGridEnabled && !state )
	{
		m_propertyGrid.DeInit();
		m_isPropertyGridEnabled = false;
	}
}

void UiManager::InitGlobalPanel()
{
	m_globalPanel.Init();
	m_globalPanel.SetColor(200,0,255);
	m_globalPanel.SetSize(250,70);
	glm::uvec2 winSize( LowLevelGraphics::WindowManager::GetInstance().GetCurrentWindowSize() );
	m_globalPanel.SetPosition(winSize.x,winSize.y);
	m_globalPanel.SetHidden(true);

	TwAddVarCB(
		m_globalPanel.GetPanel(), 
		"Enable light selection", 
		TW_TYPE_BOOLCPP,
		SetLightSelectionModeCallback, 
		GetLightSelectionModeCallback, 
		0, 
		std::string().c_str());
}

void UiManager::InitTweakBar() 
{
	//Init AntTweakBar
	TwInit(TW_OPENGL, NULL);
	glm::uvec2 winSize( LowLevelGraphics::WindowManager::GetInstance().GetCurrentWindowSize() );
	TwWindowSize( winSize.x, winSize.y );
	TwGLUTModifiersFunc(glutGetModifiers);
	TwDefine(" GLOBAL contained=true ");
}

void UiManager::DeleteTweakBar() 
{
	TwTerminate();
}

SceneManager::Component* UiManager::GetSelectedComponent() const
{
	return m_componentSelector.GetSelectedComponent();
}

void UiManager::NotifyMouseClicked( const Events::MouseEvent& event )
{
	// Left click
	if ( event.GetClickType()== Events::LEFT_CLICK )
	{
		if ( event.GetType() == Events::MOUSE_DOWN )
		{
			OnLeftButtonDown(event);
		}
		else if ( event.GetType() == Events::MOUSE_UP )
		{
			OnLeftButtonUp(event);
		}
	}
}

void UiManager::NotifyMouseMoved( const Events::MouseEvent& event )
{
	if ( m_isLeftButtonDown && m_componentSelector.IsComponentSelected() )
	{
		if ( event.GetXPosition() >= 0 && event.GetYPosition() >= 0 )
		{
			MoveComponent( m_componentSelector.GetSelectedComponent(), event.GetXPosition(), event.GetYPosition() );
		}
	}
}

void UiManager::NotifyKeyPressed( const Events::KeyboardEvent& event )
{
	if ( event.GetKey() == 's' && event.GetEventType() == Events::KEY_PRESSED )
	{
		std::cout << "Saving selection map...";
		m_componentSelector.SaveSelectionMap();
		std::cout << "done!" << std::endl;
	}
}

void UiManager::OnLeftButtonDown( const Events::MouseEvent& event )
{
	if (m_isLeftButtonDown) //oops, glut missed an event
	{
		OnLeftButtonUp(event);
	}
	m_isLeftButtonDown = true;

	if ( m_isSelectionEnabled )
	{
		m_componentSelector.UpdateSelection( event.GetXPosition(), event.GetYPosition() );
		OnSelectionUpdated();
	}
}

void UiManager::OnLeftButtonUp( const Events::MouseEvent& event )
{
	m_isLeftButtonDown = false;
	OnSelectionUpdated();
}

void UiManager::OnSelectionUpdated()
{
	if ( m_isPropertyGridEnabled )
		m_propertyGrid.DisplayPropertyGrid( m_componentSelector.GetSelectedComponent() );
}

bool UiManager::CallbackMouseTw( int button, int state, int x, int y )
{
	if ( m_isPanelEnabled )
		return TwEventMouseButtonGLUT(button,state,x,y) == 1;
	else
		return false;
}

bool UiManager::CallbackMouseMotionTw( int x, int y )
{
	if ( m_isPanelEnabled )
		return TwEventMouseMotionGLUT(x,y) == 1;
	else
		return false;
}

bool UiManager::CallbackKeyboardInputTw( unsigned char key, int x , int y )
{
	if ( m_isPanelEnabled )
		return TwEventKeyboardGLUT(key,x,y) == 1;
	else
		return false;
}

bool UiManager::CallbackKeyboardSpecialTw( int key, int x , int y )
{
	if ( m_isPanelEnabled )
		return TwEventSpecialGLUT(key,x,y) == 1;
	else
		return false;
}

void UiManager::GetLightSelectionModeCallback( void* value, void* data )
{
	*(bool*)value = UiManager::GetInstance().IsLightSelectionModeEnabled();
}

void UiManager::SetLightSelectionModeCallback( const void* value, void* data )
{
	if ( *(bool*)value ) //light selection mode enabled
	{
		UiManager::GetComponentSelector()->SetLightSelectionMode(true);
	}
	else //light selection mode disabled
	{
		//if a light is selected, clear selection
		if ( dynamic_cast<SceneManager::PointLight*>(UiManager::GetComponentSelector()->GetSelectedComponent()) )
		{
			UiManager::GetComponentSelector()->ClearSelection();
			UiManager::GetPropertyGrid()->RemoveAllElements();
		}
		UiManager::GetComponentSelector()->SetLightSelectionMode(false);
	}
}

////////////////////////////////////////////////////////////////////////////////
/////////////// Unfinished code for the Select Behind Mode /////////////////////

// void ObjectSelector::NotifyModifierKey( const Events::KeyboardModifierEvent& event )
// {
// 	if ( event.GetModifier() == Events::KEYBOARD_ACTIVE_CTRL && event.GetEventType() == Events::KEY_RELEASED )
// 	{
// 		ClearBehindMode();
// 	}
// }


// void ObjectSelector::ClearBehindMode() //keep selected object, but erase everything else
// {
// 	m_isInBehindMode = false;
// 	m_isBehindmodeCreated = false;
// 
// 	if ( IsObjectSelected() ) //keep selected object
// 	{
// 		float distance ( m_selectedObject->first );
// 		SceneManager::Object* currentObject( m_selectedObject->second );	
// 
// 		m_intersectedObjects.clear();
// 		m_intersectedObjects[distance] = currentObject;
// 		m_selectedObject = m_intersectedObjects.find(distance);
// 	}
// }

// void ObjectSelector::SelectNextObject()
// {
// 	IntersectionList::iterator tempIter(m_selectedObject);
// 	if ( tempIter !=  m_intersectedObjects.end() )
// 	{
// 		m_selectedObject = tempIter;
// 	}
// }

}
}