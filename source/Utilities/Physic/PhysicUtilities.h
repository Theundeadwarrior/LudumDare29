#ifndef UTILITIES_PHYSIC_H
#define UTILITIES_PHYSIC_H

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace Utilities
{
	class Ray;
	class AABB;

	bool PerformCubeHitTest( 
		const Ray& ray, const glm::vec3& minCorner, const glm::vec3& maxCorner, float& o_interLength );
	bool PerformPlaneHitTest( 
		const Ray& ray, const glm::vec3& planeOrigin, const glm::vec3& planeNormal, float& o_interLength );

} // namespace Utilities
} // namespace Atum



#endif
