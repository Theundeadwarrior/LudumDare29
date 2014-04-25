#include "UserInterface/Ui/UiElement.h"
#include "UserInterface/Ui/UiUtilities.h"
#include "UserInterface/Ui/UiPanel.h"


namespace Atum
{
namespace UserInterface
{

UiElement::UiElement( const std::string& pName )
	:m_name(pName),
	m_label(""),
	m_help(""),
	m_group(""),
	m_visible(true),
	m_readOnly(false)
{}


std::string UiElement::GetParameters() const
{
	std::string parameters;

	if ( m_help != "" ){
		parameters += UI_PARAM_HELP;
		parameters += "'";
		parameters += m_help;
		parameters += "' ";
	}

	if ( m_group != "" ){
		parameters += UI_PARAM_GROUP;
		parameters += "'";
		parameters += m_group;
		parameters += "' ";
	}

	if ( m_label != "" ){
		parameters += UI_PARAM_LABEL;
		parameters += "'";
		parameters += m_label;
		parameters += "' ";
	}

	if ( !m_visible ){
		parameters += UI_PARAM_VISIBLE;
		parameters += "false ";
	}

	if ( m_readOnly ){
		parameters += UI_PARAM_READ_ONLY;
		parameters += "true ";
	}

	return parameters;
}

void UiElement::AddStringParameters( const std::string& stringToAdd )
{
	
}


////////////// FLOAT /////////////////////

UiElementFloat::UiElementFloat( const std::string& p_name, float* pValue )
	:UiElement(p_name)
{
	m_type = TW_TYPE_FLOAT;
	m_valuePtr = pValue;

	m_min =0;
	m_max = 1;
	m_step = 0.1f;
	m_keyIncr = '#';
	m_keyDecr = '#';
	m_precision = -1;
}

bool UiElementFloat::AddToPanel( const UiPanel& panel )
{
	return TwAddVarRW(
		panel.GetPanel(), 
		GetName().c_str(), 
		GetType(),
		m_valuePtr,
		GetParameters().c_str()) != 0;
}

std::string UiElementFloat::GetParameters() const
{
	std::string parameters( UiElement::GetParameters() );

	parameters += UI_PARAM_MIN;
	parameters += UiUtilities::floatToStr(m_min);
	parameters += " ";

	parameters += UI_PARAM_MAX;
	parameters += UiUtilities::floatToStr(m_max);
	parameters += " ";

	parameters += UI_PARAM_STEP;
	parameters += UiUtilities::floatToStr(m_step);
	parameters += " ";

	if ( m_keyIncr != '#'){
		parameters += UI_PARAM_KEY_INCR;
		parameters += m_keyIncr;
		parameters += " ";
	}
	if ( m_keyDecr != '#'){
		parameters += UI_PARAM_KEY_DECR;
		parameters += m_keyDecr;
		parameters += " ";
	}
	if (m_precision >=0 && m_precision <= 12 ){
		parameters += UI_PARAM_PRECISION;
		parameters += UiUtilities::intToStr(m_precision);
	}

	return parameters;
}

////////////// bOOL /////////////////////

UiElementBool::UiElementBool( const std::string& pName, bool* pValue )
	:UiElement(pName),
	m_valuePtr(pValue)
{
	m_type = TW_TYPE_BOOLCPP;
}

bool UiElementBool::AddToPanel( const UiPanel& panel )
{
	return TwAddVarRW(
		panel.GetPanel(), 
		GetName().c_str(), 
		GetType(),
		m_valuePtr,
		GetParameters().c_str()) != 0;
}

////////////// STRING /////////////////////

UiElementString::UiElementString( const std::string& pName, std::string* pValue )
	:UiElement(pName),
	m_valuePtr(pValue)
{
	m_type = TW_TYPE_STDSTRING;
}

bool UiElementString::AddToPanel( const UiPanel& panel )
{
	return TwAddVarRW(
		panel.GetPanel(), 
		GetName().c_str(), 
		GetType(),
		&m_valuePtr,
		GetParameters().c_str()) != 0;
}

}
}
