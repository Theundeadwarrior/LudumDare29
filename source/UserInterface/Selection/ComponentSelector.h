#ifndef UI_OBJECT_SELECTOR_H
#define UI_OBJECT_SELECTOR_H

#include <map>

namespace Atum
{

namespace SceneManager
{
	class Component;
}
namespace Utilities
{
	class Ray;
}

namespace UserInterface
{

class ComponentSelector
{ 
	typedef std::map<float, SceneManager::Component*> IntersectionList;

	public:
		ComponentSelector();
		~ComponentSelector();

		void UpdateSelection( int xScreenPos, int yScreenPos );
		bool IsComponentSelected() const;
		SceneManager::Component* GetSelectedComponent() const;
		void ClearSelection();

		bool IsLightSelectionEnabled() const { return m_isLightSelectionEnabled; }
		void SetLightSelectionMode( bool val ) { m_isLightSelectionEnabled = val; }

		void SaveSelectionMap(); //debug 
	
	private:
		void CreateIntersectionList( unsigned int mousePosX, unsigned int mousePosY );
		void FindIntersectedComponents( const Utilities::Ray& ray);
		void ClearIntersectionList();

		IntersectionList m_intersectedComponents;
		IntersectionList::iterator m_selectedComponent;
		bool m_isLightSelectionEnabled;

};

void MoveComponent( SceneManager::Component* const component, unsigned int mousePosX, unsigned int mousePosY );

}
}

#endif //UI_OBJECT_SELECTOR_H