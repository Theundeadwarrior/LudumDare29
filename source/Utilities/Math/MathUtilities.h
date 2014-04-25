#ifndef UTILITIES_MATH_H
#define UTILITIES_MATH_H

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace Utilities
{
	
	glm::vec3 WindowToWorldCoordinates( glm::uvec2 mousePos );
	float UniformProbability(const float& a, const float& b);

} // namespace Utilities
} // namespace Atum



#endif
