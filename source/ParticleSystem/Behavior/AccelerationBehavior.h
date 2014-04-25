#ifndef PARTICLESYSTEM_ACCELERATION_BEHAVIOR_H
#define PARTICLESYSTEM_ACCELERATION_BEHAVIOR_H

#include <vector>
#include "ParticleSystem/Behavior/Behavior.h"

namespace Atum
{
namespace ParticleSystem
{
class ParticleBatch;

class AccelerationBehavior : public Behavior
{
public:
	AccelerationBehavior(float minA, float maxA, unsigned int nbParticleBatches);
	void CreateParticleBatchProperty(unsigned int index);
	void Update(ParticleBatch& particleBatch, unsigned int index);

private:
	std::vector<float> m_particleBatchAccelerations;
	float m_minAcceleration;
	float m_maxAcceleration;
};

}
}

#endif
