#include "Utilities/Debug/Debug.h"
#include "UiPanel.h"


namespace Atum
{
namespace UserInterface
{

UiPanel::UiPanel( const std::string& pName )
{
	m_name = pName;
}

UiPanel::~UiPanel()
{
	TwDeleteBar(m_panel);
	//delete m_panel;
}

void UiPanel::Init()
{
	m_panel = TwNewBar(m_name.c_str());
	TwCopyStdStringToClientFunc(CopyStdStringToClient);
}


void UiPanel::SetHelpText( const std::string& helpText )
{
	std::string parameters;

	parameters += "'" + m_name + "'";
	parameters += " ";
	parameters += UI_PARAM_HELP;
	parameters += "'";
	parameters += helpText;
	parameters += "'";

	TwDefine(parameters.c_str());
}

void UiPanel::SetSize( int width, int height )
{
	std::string parameters;

	parameters += "'" + m_name + "'";
	parameters += " ";
	parameters += UI_PARAM_SIZE;
	parameters += "'";
	parameters += UiUtilities::intToStr(width) + " " + UiUtilities::intToStr(height);
	parameters += "'";

	TwDefine(parameters.c_str());
}

void UiPanel::SetColor( int R, int G, int B )
{
	std::string parameters;

	parameters += "'" + m_name + "'";
	parameters += " ";
	parameters += UI_PARAM_COLOR;
	parameters += "'";
	parameters +=	UiUtilities::intToStr(R) + " " + 
					UiUtilities::intToStr(G) + " " +
					UiUtilities::intToStr(B);
	parameters += "'";
	parameters += " alpha=255 ";

	TwDefine(parameters.c_str());
}

void UiPanel::SetHidden( bool state )
{
	std::string parameters;

	parameters += "'" + m_name + "'";
	parameters += " ";
	parameters += UI_PARAM_HIDDEN;
	parameters += " ";
	
	if ( state )
		parameters += "true";
	else
		parameters += "false";

	TwDefine(parameters.c_str());
}

void UiPanel::SetPosition( int x, int y )
{
	std::string parameters;

	parameters += "'" + m_name + "'";
	parameters += " ";
	parameters += UI_PARAM_POSITION;
	parameters += "'";
	parameters +=	UiUtilities::intToStr(x) + " " + 
		UiUtilities::intToStr(y);
	parameters += "'";

	TwDefine(parameters.c_str());
}

bool UiPanel::RemoveAllElements()
{
	return TwRemoveAllVars(m_panel) == 1;
}

bool UiPanel::RemoveElement( const std::string& name )
{
	return TwRemoveVar(m_panel, name.c_str()) == 1;
}


bool UiPanel::FoldGroup( bool foldStatus, const std::string& groupName )
{
	std::string parameters;

	parameters += "'" + m_name + "'" + "//" + groupName + " ";
	parameters +=  UI_PARAM_OPENED;

	if (foldStatus == true){
		parameters += "true";
	}
	else {
		parameters += "false";
	}
	return TwDefine(parameters.c_str()) == 1;
}

void UiPanel::RefreshPanel()
{
	TwRefreshBar(m_panel);
}

void UiPanel::FitColumnContent()
{
	std::string parameters;

	parameters += "'" + m_name + "' ";
	parameters +=  UI_PARAM_FIT_COLUMN;
	parameters += "fit";

	//TwDefine(parameters.c_str());
	TwDefine(" 'Object Properties' valueswidth=fit "); 
}

void UiPanel::AddReadOnlyString( const std::string& roString, const std::string& parameters )
{
	if ( roString != "" )
	{
		TwAddButton(m_panel, roString.c_str(), NULL, NULL, parameters.c_str());
	}
}

void TW_CALL UiPanel::CopyStdStringToClient( std::string& destinationClientString, const std::string& sourceLibraryString )
{
	destinationClientString = sourceLibraryString;
}

void UiPanel::AddSeparator( const std::string& parameters )
{
	TwAddSeparator( m_panel, NULL, parameters.c_str() );
}


}
}