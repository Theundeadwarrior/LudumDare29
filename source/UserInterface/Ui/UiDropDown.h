#ifndef UI_DROPDOWN_H
#define UI_DROPDOWN_H

#include <string>

#include "AntTweakBar/include/AntTweakBar.h"
#include "UserInterface/Ui/UiElement.h"
#include <vector>
#include <utility>

namespace Atum
{
namespace UserInterface
{

class UiPanel;

class UiDropDown: public UiElement
{ 
	public:
		UiDropDown( const std::string& pName, const std::vector<std::pair<int,std::string>>& selectionList );
		~UiDropDown();

		bool AddToPanel( const UiPanel& panel );
		
		int GetSelection() const { return m_selection; }
		void SetSelection( int selection ) { m_selection = selection; }
		
		TwType GetEnumType() const { return m_selectionType; }

	private:
		TwEnumVal* m_selectionEnum;
		TwType m_selectionType;
		int m_selection;
};


}
}

#endif //UI_BUTTON_H


