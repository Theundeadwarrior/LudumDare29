#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "UiPanel.h"
#include <map>
#include "AntTweakBar/include/AntTweakBar.h"

#include "UserInterface/Ui/UiPropertyGrid.h"
#include "UserInterface/Selection/ComponentSelector.h"
#include "UserInterface/Ui/UiElement.h"

#include "Events/InputMouseListener.h"
#include "Events/InputKeyboardListener.h"

namespace Atum
{

namespace SceneManager
{
	class Object;
}

namespace UserInterface
{

class UiManager : private Events::InputMouseListener, private Events::InputKeyboardListener
{
	public:
		~UiManager();
		static UiManager& GetInstance();

		void EnableCompleteUi(); //use this if you don't know what to do
		void DisableCompleteUi();

		void SetCompleteUiState( bool state );
		void SetEventsState( bool state );
		void SetPanelsState( bool state );
		void SetObjectSelectionState( bool state );
		void SetPropertyGridState( bool state );
		void InitGlobalPanel();

		SceneManager::Component* GetSelectedComponent() const;
		bool IsLightSelectionModeEnabled() const { return m_componentSelector.IsLightSelectionEnabled(); }
		void DrawPanels();

		//for events, later...
		void WindowResized(int width, int height);

		//Ui AntTweakBar callback functions
		static bool CallbackMouseTw ( int button, int state, int x, int y );
		static bool CallbackMouseMotionTw ( int x, int y );
		static bool CallbackKeyboardInputTw ( unsigned char key, int x , int y );
		static bool CallbackKeyboardSpecialTw ( int key, int x , int y );

		static void TW_CALL GetLightSelectionModeCallback( void* value, void* data);
		static void TW_CALL SetLightSelectionModeCallback( const void* value, void* data);

		static UiPropertyGrid* const GetPropertyGrid() { return &m_propertyGrid; }
		static ComponentSelector* const GetComponentSelector() { return &m_componentSelector; }

	private:
		// UI events functions
		void OnLeftButtonDown	( const Events::MouseEvent& event );
		void OnLeftButtonUp		( const Events::MouseEvent& event );
		void OnMouseMove		( const Events::MouseEvent& event );
		void OnSelectionUpdated	();

		// Ui listening functions
		void NotifyMouseClicked	( const Events::MouseEvent& event );
		void NotifyMouseMoved	( const Events::MouseEvent& event );
		void NotifyKeyPressed	( const Events::KeyboardEvent& event );

		//Ui utilities
		void InitTweakBar();
		void DeleteTweakBar();

		// Ui members
		static bool m_isLeftButtonDown;
		static UiPropertyGrid m_propertyGrid;
		static ComponentSelector m_componentSelector;
		static UiPanel m_globalPanel;

		static bool m_isEventEnabled;
		static bool m_isPanelEnabled;
		static bool m_isSelectionEnabled;
		static bool m_isPropertyGridEnabled;

		// Singleton
		UiManager();
		UiManager(UiManager const&);      // Don't Implement
		void operator=(UiManager const&); // Don't implement
};

}
}

#endif //UI_MANAGER_h