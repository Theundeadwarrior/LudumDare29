#ifndef PARTICLESYSTEM_MULTICOLOR_BEHAVIOR_H
#define PARTICLESYSTEM_MULTICOLOR_BEHAVIOR_H

#include "ParticleSystem/Behavior/Behavior.h"
#include "GLM/include/glm/glm.hpp"
#include <vector>

namespace Atum
{
namespace ParticleSystem
{
class MultiColorBehavior : public Behavior
{
public:
	MultiColorBehavior(unsigned int nbParticleBatches){m_particleBatchMultiColor.resize(nbParticleBatches);}
	void CreateParticleBatchProperty(unsigned int index);
	void Update(ParticleBatch& particleBatch, unsigned int index);
private:
	std::vector<glm::vec3> m_particleBatchMultiColor;
};
}
}

#endif

