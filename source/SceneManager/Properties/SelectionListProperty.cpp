#include "SelectionListProperty.h"

namespace Atum
{
namespace SceneManager
{

	SelectionListProperty::SelectionListProperty(
		const std::string& listName, const std::vector<std::pair<int,std::string>>* const selectionList, int currentID )
		:Property(listName, currentID),
		m_selectionList(selectionList)
	{
		m_type = PROPERTY_SELECTION_LIST;
	}

	SelectionListProperty::~SelectionListProperty()
	{}

	const std::vector<std::pair<int,std::string>>* const SelectionListProperty::GetSelectionList() const
	{
		return m_selectionList;
	}

}
}
