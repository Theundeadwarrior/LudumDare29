#ifndef PARTICLESYSTEM_ORBITAL_BEHAVIOR_H
#define PARTICLESYSTEM_ORBITAL_BEHAVIOR_H

#include "ParticleSystem/Behavior/Behavior.h"
#include "AttractorRepulsor.h"
#include <vector>
namespace Atum
{
namespace ParticleSystem
{
class ParticleBatch;
class OrbitalBehavior : public Behavior
{
public:
	OrbitalBehavior(std::vector<AttractorRepulsor> centers):m_centers(centers){}
	void CreateParticleBatchProperty(unsigned int index){}
	void Update(ParticleBatch& particleBatch, unsigned int index);

private:
	std::vector<AttractorRepulsor> m_centers;
};
}
}

#endif
