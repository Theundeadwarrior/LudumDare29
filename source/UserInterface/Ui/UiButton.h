#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <string>

#include "AntTweakBar/include/AntTweakBar.h"
#include "UserInterface/Ui/UiElement.h"

namespace Atum
{
namespace UserInterface
{

class UiPanel;

class UiButton: public UiElement
{ 
	public:
		UiButton( const std::string& pName, void (*callbackFunction)(void*), void* funcData );
		~UiButton();

		bool AddToPanel( const UiPanel& panel );
		void ExecuteCallbackFunction();

	private:
		void (*m_FuncToCall)(void*);
		void* m_funcData;
};


void TW_CALL ButtonCallback(void* clientData);

}
}

#endif //UI_BUTTON_H


