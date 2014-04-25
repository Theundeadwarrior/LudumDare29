#ifndef PARTICLESYSTEM_EXPLODINGSIZE_BEHAVIOR_H
#define PARTICLESYSTEM_EXPLODINGSIZE_BEHAVIOR_H

#include "ParticleSystem/Behavior/Behavior.h"
#include "GLM/include/glm/glm.hpp"
#include <vector>

namespace Atum
{
namespace ParticleSystem
{
class ExplodingSizeBehavior : public Behavior
{
public:
	void Update(ParticleBatch& particleBatch, unsigned int index);
};
}
}

#endif

