#ifndef SCENEMANAGER_PROPERTYLIST_CPP
#define SCENEMANAGER_PROPERTYLIST_CPP

#include "PropertyList.h"
#include <list>

namespace Atum
{
namespace SceneManager
{

	//-----------------------------------------------------------------------------
	PropertyList::PropertyList()
	{}

	//-----------------------------------------------------------------------------
	PropertyList::~PropertyList()
	{
		ClearPropertyList();
	}

	//-----------------------------------------------------------------------------
	void PropertyList::ClearPropertyList()
	{
		while(!m_propertyList.empty())
		{
			delete m_propertyList.front(), m_propertyList.pop_front();
		}
	}

	//-----------------------------------------------------------------------------
	bool PropertyList::AddProperty( Property* pProperty )
	{
		if ( FindProperty(pProperty->GetName()) == m_propertyList.end() ) //property name is not used
		{
			m_propertyList.push_back(pProperty);
			return true;
		}
		else
		{
			delete pProperty;
			return false;
		}
	}

	//-----------------------------------------------------------------------------
	Property const* PropertyList::GetProperty( const std::string& pName ) const
	{
		PropIterator iter = FindProperty(pName) ;
		if (iter != m_propertyList.end() )
		{
			return *iter;
		}
		else
		{
			return 0;
		}
	}

	//-----------------------------------------------------------------------------
	bool PropertyList::DeleteProperty( const std::string& pName )
	{
		PropIterator iter( FindProperty(pName) );
		if ( iter != m_propertyList.end() ) //property exists
		{
			m_propertyList.erase(iter);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------------
	PropertyList::PropIterator PropertyList::FindProperty( const std::string& name ) const
	{
		PropIterator iter (m_propertyList.begin());
		for ( ; iter != m_propertyList.end(); iter++)
		{
			if ( (*iter)->GetName() == name )
				return iter;
		}

		return m_propertyList.end();
	}

} // namespace SceneManager
} // namespace Atum

#endif // SCENEMANAGER_PROPERTYLIST_CPP
