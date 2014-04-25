#ifndef UTILITIES_AABB_H
#define UTILITIES_AABB_H

#include "GLM/include/glm/glm.hpp"
#include <vector>
#include "OBB.h"

namespace Atum { namespace SceneManager { class PropertyList; class Transform; }}

namespace Atum
{
namespace Utilities
{
	const float DEFAULT_MIN_BOUNDS = 999999;
	const float DEFAULT_MAX_BOUNDS = -999999;

	class AABB
	{
	public:
		AABB();
		AABB(const glm::vec3 & minBounds, const glm::vec3 & maxBounds);
		~AABB();
        void UpdateBoundingBox(const std::vector<glm::vec3>& geom, const Atum::SceneManager::Transform& transform);
        void UpdateBoundingBox(const OBB& obb, const Atum::SceneManager::Transform& transform);

		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
	};

} // namespace Utilities
} // namespace Atum


#endif