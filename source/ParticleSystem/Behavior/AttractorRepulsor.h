#ifndef PARTICLESYSTEM_ATTRACTOR_REPULSOR_H
#define PARTICLESYSTEM_ATTRACTOR_REPULSOR_H

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace ParticleSystem
{
struct AttractorRepulsor
{
	AttractorRepulsor(glm::vec3 p, float f):position(p),force(f){}

	glm::vec3 position;
	float force;
};
}
}

#endif
