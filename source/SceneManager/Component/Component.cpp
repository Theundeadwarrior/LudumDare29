#include "Component.h"

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace SceneManager
{

	Component::Component()
		:m_aabb(glm::vec3(),glm::vec3()),
		m_name()
	{}
	
	Component::~Component()
	{}

	void Component::UpdateAABB()
	{}

	void Component::GetPropertyList( PropertyList& o_properties ) const
	{}

	void Component::UpdatePropertyList( const PropertyList& i_properties )
	{}

	Atum::Utilities::AABB Component::GetAABB()
	{
		return m_aabb;
	}

} // namespace SceneManager
} // namespace Atum
