#ifndef PARTICLESYSTEM_FOLLOW_BEHAVIOR_H
#define PARTICLESYSTEM_FOLLOW_BEHAVIOR_H

#include "ParticleSystem/Behavior/Behavior.h"
#include "ParticleSystem/Behavior/AttractorRepulsor.h"
#include <vector>

namespace Atum
{
namespace ParticleSystem
{
class FollowBehavior : public Behavior
{
public:
	FollowBehavior(std::vector<AttractorRepulsor> centers):m_centers(centers){}
	void CreateParticleBatchProperty(unsigned int index){}
	void Update(ParticleBatch& particleBatch, unsigned int index);

private:
	std::vector<AttractorRepulsor> m_centers;
};
}
}

#endif
