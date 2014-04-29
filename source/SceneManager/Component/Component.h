#ifndef SCENEMANAGER_COMPONENT_H
#define SCENEMANAGER_COMPONENT_H

#include "GLM/include/glm/glm.hpp"
#include "LowLevelGraphics/Geometry/Geometry.h"

#include "Utilities/Physic/AABB.h"

#define COMP_PROP_NAME "Name"
#define COMP_PROP_POSITION "Position"
#define COMP_PROP_SCALE "Scale"
#define COMP_PROP_ROTATION "Rotation"

namespace Atum
{
namespace SceneManager
{
	class PropertyList; 
}

namespace SceneManager
{
	class Component
	{
		public:
			Component();
			virtual ~Component()=0;

			virtual void GetPropertyList ( PropertyList& o_properties ) const;
			virtual void UpdatePropertyList ( const PropertyList& i_properties );

			virtual void UpdateAABB();
			virtual Atum::Utilities::AABB GetAABB();

			std::string GetName() const { return m_name; }
			void SetName(const std::string& newName) { m_name = newName; }

		protected:
			std::string m_name;
			Utilities::AABB m_aabb;
	};

	} // namespace SceneManager
} // namespace Atum


#endif
