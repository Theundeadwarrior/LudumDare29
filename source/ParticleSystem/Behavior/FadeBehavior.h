#ifndef PARTICLESYSTEM_FADE_BEHAVIOR_H
#define PARTICLESYSTEM_FADE_BEHAVIOR_H

#include "ParticleSystem/Behavior/Behavior.h"
#include <vector>

namespace Atum
{
namespace ParticleSystem
{
class FadeBehavior : public Behavior
{
public:
	void Update(ParticleBatch& particleBatch, unsigned int index);
};
}
}

#endif

