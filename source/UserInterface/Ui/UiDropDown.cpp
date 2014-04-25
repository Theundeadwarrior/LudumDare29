#include "UiDropDown.h"
#include "UserInterface/Ui/UiPanel.h"

namespace Atum
{
namespace UserInterface
{


UiDropDown::UiDropDown( const std::string& pName, const std::vector<std::pair<int,std::string>>& selectionList )
	:UiElement(pName),
	m_selection(0)
{
	m_selectionEnum = new TwEnumVal[selectionList.size()];
	
	for ( unsigned int i =0; i < selectionList.size(); i++ )
	{
		m_selectionEnum[i].Value = selectionList[i].first;
		m_selectionEnum[i].Label = selectionList[i].second.c_str();
	}
	
	m_selectionType = TwDefineEnum( (pName+"Type").c_str(), m_selectionEnum, selectionList.size() );
}

UiDropDown::~UiDropDown()
{
	delete[] m_selectionEnum;
}

bool UiDropDown::AddToPanel( const UiPanel& panel )
{
	return TwAddVarRW(
		panel.GetPanel(), 
		GetName().c_str(), 
		m_selectionType,
		&m_selection,
		GetParameters().c_str()) != 0;
}

///////////////////////////

}
}
