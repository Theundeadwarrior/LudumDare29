#ifndef SELECTION_PROPERTY_T_H
#define SELECTION_PROPERTY_T_H

#include <string>
#include <vector>
#include <utility>
#include "Property.h"

namespace Atum
{
namespace SceneManager
{
	class SelectionListProperty: public Property {

		public:
			SelectionListProperty( 
				const std::string& listName, const std::vector<std::pair<int,std::string>>* const selectionList, int currentID );
			~SelectionListProperty();

			const std::vector<std::pair<int,std::string>>* const GetSelectionList() const;

		private:
			const std::vector<std::pair<int,std::string>>* const m_selectionList;
	};

}
}

#endif //SELECTION_PROPERTY_T_H