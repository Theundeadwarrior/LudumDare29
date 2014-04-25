#ifndef PARTICLESYSTEM_BEHAVIOR_H
#define PARTICLESYSTEM_BEHAVIOR_H

namespace Atum
{
namespace ParticleSystem
{
class ParticleBatch;

class Behavior
{
public:
	virtual ~Behavior(void) = 0{}
	virtual void CreateParticleBatchProperty(unsigned int index){}
	virtual void Update(ParticleBatch& particle, unsigned int index){}
};

}
}

#endif
