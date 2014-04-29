#include "UiPropertyGrid.h"
#include <iostream>
#include <utility>

#include "GLM/include/glm/glm.hpp"
#include "GLM/include/glm/gtx/quaternion.hpp"

#include "SceneManager/Objects/Object.h"
#include "SceneManager/Objects/PointCloud.h"
#include "SceneManager/Properties/Property.h"
#include "SceneManager/Properties/SelectionListProperty.h"
#include "SceneManager/Properties/TextureProperty.h"
#include "SceneManager/Manager/MaterialManager.h"

#include "UserInterface/Ui/UiButton.h"
#include "UserInterface/Ui/UiDropDown.h"

namespace Atum
{
namespace UserInterface
{

PanelPropertyMap UiPropertyGrid::m_propertyPanelMapping;

UiPropertyGrid::UiPropertyGrid( const std::string& pName )
	:UiPanel(pName)
{}

UiPropertyGrid::~UiPropertyGrid()
{
}

void UiPropertyGrid::Init()
{
	UiPanel::Init();
	UiPanel::SetColor(120,175,200);
	UiPanel::SetSize(250,200);
}

void UiPropertyGrid::DeInit()
{
	DeleteGrid();
	TwDeleteBar(m_panel);
}

void UiPropertyGrid::DisplayPropertyGrid( SceneManager::Component* object )
{
	DeleteGrid();

	if (object)
	{
		m_component = object;
		CreateGrid();
	}
}

void UiPropertyGrid::CreateGrid()
{

}

void UiPropertyGrid::DeleteGrid()
{

}

void UiPropertyGrid::RefreshPropertyGrid()
{
	
}

void UiPropertyGrid::SetGroup( SceneManager::Property* property, const std::string& group ) const
{

}

/////////////// Add new types here ///////////////////////

void UiPropertyGrid::AddElement( SceneManager::Property* property, const std::string& group )
{
	
}

void UiPropertyGrid::AddTextureElement( SceneManager::Property* property, const std::string& group )
{
	
}

void UiPropertyGrid::AddDropDownElement( SceneManager::Property* property, const std::string& group )
{
	
}

void UiPropertyGrid::UpdatePropertyList()
{

}

/////////////////////////////////////////////////
void TW_CALL UiPropertyGrid::GetCallbackPropertyInt(void* value, void* clientData)
{ 
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(int*)value );
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyInt( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	bool treest= property->SetValue( *(const int*)value );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyFloat(void* value, void* clientData)
{ 
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(float*)value );
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyFloat( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->SetValue( *(const float*)value );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyDouble( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(double*)value );
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyDouble( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->SetValue( *(const double*)value );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyBool( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(bool*)value );
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyBool( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->SetValue( *(const bool*)value );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyString( void* value, void* clientData )
{
	std::string *destPtr = static_cast<std::string *>(value);

	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(std::string*)value );
	TwCopyStdStringToLibrary(*destPtr, *(std::string*)value); // Get: copy the value of s to AntTweakBar
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyString( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->SetValue( *(const std::string*)value );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyVector3f( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );

	glm::vec3 vector3;
 	property->GetValue( vector3 );
	((float*)value)[0] = vector3.x;
	((float*)value)[1] = vector3.y;
	((float*)value)[2] = vector3.z;
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyVector3f( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	
	glm::vec3 vector3;
	vector3.x = ((float*)value)[0];
	vector3.y = ((float*)value)[1];
	vector3.z = ((float*)value)[2];
	property->SetValue( vector3 );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyVector4f( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );

	glm::vec4 vector4;
	property->GetValue( vector4 );
	((float*)value)[0] = vector4.x;
	((float*)value)[1] = vector4.y;
	((float*)value)[2] = vector4.z;
	((float*)value)[3] = vector4.w;
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyVector4f( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );

	glm::vec4 vector4;
	vector4.x = ((float*)value)[0];
	vector4.y = ((float*)value)[1];
	vector4.z = ((float*)value)[2];
	vector4.w = ((float*)value)[3];
	property->SetValue( vector4 );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyQuat( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );

	glm::quat quaternion;
	property->GetValue( quaternion );
	((float*)value)[0] = quaternion.x;
	((float*)value)[1] = quaternion.y;
	((float*)value)[2] = quaternion.z;
	((float*)value)[3] = quaternion.w;
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyQuat( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );

	glm::quat quaternion;
	quaternion.x = ((float*)value)[0];
	quaternion.y = ((float*)value)[1];
	quaternion.z = ((float*)value)[2];
	quaternion.w = ((float*)value)[3];
	property->SetValue( quaternion );
	GetParentPanel(property)->UpdatePropertyList();
}

void TW_CALL UiPropertyGrid::GetCallbackPropertyDropdown( void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	property->GetValue( *(int*)value );
}

void TW_CALL UiPropertyGrid::SetCallbackPropertyDropdown( const void* value, void* clientData )
{
	SceneManager::Property* property ( reinterpret_cast<SceneManager::Property*>(clientData) );
	bool treest= property->SetValue( *(const int*)value );
	GetParentPanel(property)->UpdatePropertyList();
	GetParentPanel(property)->RefreshPropertyGrid();
}


///////////////////// STATIC FUNCTIONS //////////////////////////////////////

void UiPropertyGrid::ClearElementList()
{
	while(!m_elementList.empty())
	{
		delete m_elementList.front(), m_elementList.pop_front();
	}
}

void UiPropertyGrid::ClearPanelPropertyMapping( UiPanel* panelToClear )
{
	PanelPropertyMap::iterator it( m_propertyPanelMapping.begin() );

	while (it != m_propertyPanelMapping.end()) 
	{
		if ( it->second == panelToClear )
			m_propertyPanelMapping.erase(it++);
		else
			it++;
	}
}

UiPropertyGrid* UiPropertyGrid::GetParentPanel( SceneManager::Property* property )
{
	return m_propertyPanelMapping.find(property)->second;
}

void UiPropertyGrid::AddPropertyMapping( SceneManager::Property* property, UiPropertyGrid* panel )
{
	m_propertyPanelMapping[property] = panel;
}


//////////////////////// STATIC CALLBACK FUNCTIONS ///////////////////////////

void UiPropertyGrid::CreateTextureCallback( void* propertyData )
{
	SceneManager::Property* textureProperty ( reinterpret_cast<SceneManager::Property*>(propertyData) );

	std::vector<std::string> extensionList;
	extensionList.push_back("*.bmp; *.png");
	std::string filePath( UiUtilities::DisplayOpenFileDialog(extensionList) );
	if ( filePath != "" )
	{
		textureProperty->SetValue(filePath);
		UiPropertyGrid* currentPropertyGrid( GetParentPanel(textureProperty) );
		if ( currentPropertyGrid )
		{
			currentPropertyGrid->UpdatePropertyList();
			currentPropertyGrid->RefreshPropertyGrid();
		}
	}

}

void UiPropertyGrid::ClearTextureCallback( void* propertyData )
{
	SceneManager::Property* textureProperty ( reinterpret_cast<SceneManager::Property*>(propertyData) );
	std::string nullString;
	textureProperty->SetValue(nullString);

	UiPropertyGrid* currentPropertyGrid( GetParentPanel(textureProperty) );
	currentPropertyGrid->UpdatePropertyList();
	currentPropertyGrid->RefreshPropertyGrid();

}

}
}
