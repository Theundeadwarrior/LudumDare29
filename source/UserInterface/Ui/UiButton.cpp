#include "UiButton.h"
#include "UserInterface/Ui/UiPanel.h"

namespace Atum
{
namespace UserInterface
{


UiButton::UiButton( const std::string& pName, void (*callbackFunction)(void*), void* funcData )
	:UiElement(pName), m_funcData(funcData)
{
	m_FuncToCall = callbackFunction;
}

UiButton::~UiButton()
{}

bool UiButton::AddToPanel( const UiPanel& panel )
{
	return TwAddButton(
		panel.GetPanel(), 
		GetName().c_str(), 
		ButtonCallback,
		this,
		GetParameters().c_str()) != 0;
}

void UiButton::ExecuteCallbackFunction()
{
	return m_FuncToCall(m_funcData);
}

///////////////////////////

void TW_CALL ButtonCallback( void* clientData )
{
	UiButton* button( reinterpret_cast<UiButton*>(clientData) );
	if ( button )
	{
		button->ExecuteCallbackFunction();
	}
}

}
}
