#ifndef SCENEMANAGER_PROPERTYLIST_H
#define SCENEMANAGER_PROPERTYLIST_H

#include "Property.h"
#include <string>
#include <list>

namespace Atum
{
namespace SceneManager
{
	class PropertyList
	{
	public:
		typedef std::list< Property* >::const_iterator PropIterator;

		PropertyList();
		~PropertyList();

		bool AddProperty( Property* pProperty);
		Property const* GetProperty( const std::string& pName ) const;
		const std::list<Property*>& GetProperties() const { return m_propertyList; }
		bool DeleteProperty( const std::string& pName );

		int GetPropertyCount() const { return m_propertyList.size(); }
		void ClearPropertyList();

	private:
		PropIterator FindProperty(const std::string& name) const;

		std::list<Property*> m_propertyList;
	};

} // namespace SceneManager
} // namespace Atum

#endif // SCENEMANAGER_PROPERTYLIST_H
