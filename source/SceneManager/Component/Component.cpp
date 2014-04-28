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

	Atum::Utilities::AABB Component::GetAABB()
	{
		return m_aabb;
	}

} // namespace SceneManager
} // namespace Atum
