#ifndef UI_PROPERTIES_H
#define UI_PROPERTIES_H

#include <list>

#include "UserInterface/Ui/UiPanel.h"
#include "UserInterface/Ui/UiPropertyGrid.h"
#include "UserInterface/Ui/UiElement.h"
#include "SceneManager/Component/Component.h"
#include "SceneManager/Properties/PropertyList.h"

namespace Atum
{

namespace SceneManager
{
	class Property;
}

namespace UserInterface
{
	class UiPropertyGrid;
	typedef std::map< SceneManager::Property*, UiPropertyGrid* > PanelPropertyMap;

	class UiPropertyGrid : public UiPanel
	{
		public:
			UiPropertyGrid(const std::string& pName);
			~UiPropertyGrid();

			void Init();
			void DeInit();
			void DisplayPropertyGrid( SceneManager::Component* object );
			void RefreshPropertyGrid();

			void UpdatePropertyList(); //connected with the object

		private:
			void CreateGrid();
			void DeleteGrid();
			void AddElement( SceneManager::Property* property, const std::string& group="" );
			void AddTextureElement( SceneManager::Property* property, const std::string& group="" );
			void AddDropDownElement( SceneManager::Property* property, const std::string& group="" );

			void ClearElementList();
			void SetGroup( SceneManager::Property* property, const std::string& group ) const;
	
			SceneManager::Component* m_component;
			SceneManager::PropertyList m_propertyList;
			std::list<UiElement*> m_elementList;

			/////////////////// Static shit /////////////////////

			//Callbacks for getting and updating properties
			static void TW_CALL GetCallbackPropertyInt		(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyInt		(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyFloat	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyFloat	(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyDouble	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyDouble	(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyBool		(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyBool		(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyString	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyString	(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyVector3f	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyVector3f	(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyVector4f	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyVector4f	(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyQuat		(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyQuat		(const void* value, void* clientData);
			static void TW_CALL GetCallbackPropertyDropdown	(void* value, void* clientData);
			static void TW_CALL SetCallbackPropertyDropdown	(const void* value, void* clientData);

			//Buttons callbacks
			static void CreateTextureCallback( void* propertyData );
			static void ClearTextureCallback( void* propertyData );

			static void AddPropertyMapping( SceneManager::Property* property, UiPropertyGrid* panel );
			static void ClearPanelPropertyMapping( UiPanel* panelToClear );
			static UiPropertyGrid* GetParentPanel( SceneManager::Property* property );

			static PanelPropertyMap m_propertyPanelMapping;
};

}
}

#endif //UI_PROPERTIES_H

