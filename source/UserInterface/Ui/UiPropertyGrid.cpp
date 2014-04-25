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
	//Add object properties
	m_component->GetPropertyList( m_propertyList );
	SceneManager::PropertyList::PropIterator pIter( m_propertyList.GetProperties().begin() );
	SceneManager::PropertyList::PropIterator pIterBeforeAdd( pIter );
	for ( ; pIter != m_propertyList.GetProperties().end() ; pIter++)
	{
		AddElement( *pIter );
		pIterBeforeAdd = pIter;
	}

	SceneManager::Object* object( dynamic_cast<SceneManager::Object*>(m_component) );
	SceneManager::PointCloud* pointCloud (dynamic_cast<SceneManager::PointCloud*>(m_component));
	if ( object && !pointCloud )
	{
		//Add Lighting properties
		object->GetMaterial()->GetLightingPropertyList( m_propertyList );
		pIter = ++pIterBeforeAdd;
		for ( ; pIter != m_propertyList.GetProperties().end() ; pIter++)
		{
			AddElement( *pIter,UI_LIGHTING_TECH_GROUP );
			pIterBeforeAdd = pIter;
		}

		//Add Effects properties
		object->GetMaterial()->GetEffectPropertyList( m_propertyList );
		pIter = ++pIterBeforeAdd;
		for ( ; pIter != m_propertyList.GetProperties().end() ; pIter++)
		{
			AddElement( *pIter,UI_EFFECTS_GROUP );
			pIterBeforeAdd = pIter;
		}
	}
}

void UiPropertyGrid::DeleteGrid()
{
	TwRemoveAllVars(m_panel);

	ClearElementList();
	ClearPanelPropertyMapping(this);
	m_propertyList.ClearPropertyList();
}

void UiPropertyGrid::RefreshPropertyGrid()
{
	DisplayPropertyGrid(m_component);
}

void UiPropertyGrid::SetGroup( SceneManager::Property* property, const std::string& group ) const
{
	std::string groupParam(UI_PARAM_GROUP);
	property->AddParameter(groupParam + "'" + group + "'" );
}

/////////////// Add new types here ///////////////////////

void UiPropertyGrid::AddElement( SceneManager::Property* property, const std::string& group )
{
	AddPropertyMapping(property, this); //don't touch!

	if ( group.size() != 0 ) SetGroup(property,group);
	if( property->GetType() == SceneManager::PROPERTY_INT )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_INT32, 
			SetCallbackPropertyInt, 
			GetCallbackPropertyInt, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_FLOAT )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_FLOAT, 
			SetCallbackPropertyFloat, 
			GetCallbackPropertyFloat, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_DOUBLE )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_DOUBLE, 
			SetCallbackPropertyDouble, 
			GetCallbackPropertyDouble, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_BOOL )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_BOOLCPP, 
			SetCallbackPropertyBool, 
			GetCallbackPropertyBool, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_STRING )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_STDSTRING, 
			SetCallbackPropertyString, 
			GetCallbackPropertyString, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_VECTOR3F )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_DIR3F, 
			SetCallbackPropertyVector3f, 
			GetCallbackPropertyVector3f, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_VECTOR4F )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_COLOR4F, 
			SetCallbackPropertyVector4f, 
			GetCallbackPropertyVector4f, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_QUATERNION )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_QUAT4F, 
			SetCallbackPropertyQuat, 
			GetCallbackPropertyQuat, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_COLOR )
	{
		TwAddVarCB(m_panel, 
			property->GetName().c_str(),
			TW_TYPE_COLOR3F, 
			SetCallbackPropertyVector3f, 
			GetCallbackPropertyVector3f, 
			property, 
			property->GetParameters().c_str() );
	}
	else if ( property->GetType() == SceneManager::PROPERTY_TEXTURE )
	{
		AddTextureElement(property,group);
	}
	else if ( property->GetType() == SceneManager::PROPERTY_SELECTION_LIST )
	{
		AddDropDownElement(property,group);
	}
}

void UiPropertyGrid::AddTextureElement( SceneManager::Property* property, const std::string& group )
{
	std::string groupParam( std::string(UI_PARAM_GROUP) + "'" + group + "'" );
	AddSeparator(groupParam);

	//Add path selected
	std::string path;
	property->GetValue(path);
	bool IsFileSet = false;
	std::string file;
	if ( path.size() == 0 )
	{
		file = "Not set";
	}
	else
	{
		IsFileSet = true;
		file = UiUtilities::GetFileFromPath(path) ;
	}
	std::string pathLabel( property->GetName() + " texture: ");
	AddReadOnlyString(pathLabel+file, groupParam );

	//Add select texture button
	std::string selectButtonLabel( "Select " + property->GetName() + " texture...");
	UiButton* selectTexture = new UiButton(selectButtonLabel, CreateTextureCallback, property);
	selectTexture->SetLabel(selectButtonLabel);
	selectTexture->SetGroup(group);
	m_elementList.push_back( selectTexture );
	selectTexture->AddToPanel(*this);

	//Add clear texture button
	if ( IsFileSet )
	{
		std::string clearButtonLabel( "Clear " + property->GetName() + " texture" );
		UiButton* clearTexture = new UiButton(clearButtonLabel, ClearTextureCallback, property);
		clearTexture->SetLabel(clearButtonLabel);
		clearTexture->SetGroup(group);
		m_elementList.push_back( clearTexture );
		clearTexture->AddToPanel(*this);
	}

	AddSeparator(groupParam);
}

void UiPropertyGrid::AddDropDownElement( SceneManager::Property* property, const std::string& group )
{
	SceneManager::SelectionListProperty* dropDownProp( dynamic_cast<SceneManager::SelectionListProperty*>(property) );
	if ( dropDownProp )
	{
		std::string dropDownLabel( property->GetName() + " :" );
		UiDropDown* dropDown = new UiDropDown( dropDownLabel, *dropDownProp->GetSelectionList() );
		dropDown->SetGroup(group);

		///Get id and set it
		int selectionID;
		dropDownProp->GetValue(selectionID);
		m_elementList.push_back(dropDown);

		//Add to the panel
		TwAddVarCB(m_panel, 
			dropDown->GetName().c_str(),
			dropDown->GetEnumType(), 
			SetCallbackPropertyDropdown, 
			GetCallbackPropertyDropdown, 
			property, 
			dropDown->GetParameters().c_str() );
	}
}

void UiPropertyGrid::UpdatePropertyList()
{
	m_component->UpdatePropertyList( m_propertyList );
	SceneManager::Object* object (dynamic_cast<SceneManager::Object*>(m_component));
	SceneManager::PointCloud* pointCloud (dynamic_cast<SceneManager::PointCloud*>(m_component));
	if (object && !pointCloud)
	{
		object->GetMaterial()->UpdateLightingPropertyList(m_propertyList);
		object->GetMaterial()->UpdateEffectPropertyList(m_propertyList);
		//RefreshPropertyGrid();
	}
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
