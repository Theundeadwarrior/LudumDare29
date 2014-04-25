#ifndef PARTICLESYSTEM_DESPAWNER_H
#define PARTICLESYSTEM_DESPAWNER_H

namespace Atum
{
namespace ParticleSystem
{
class ParticleBatch;

class Despawner
{
public:
	Despawner(bool isActive = false):m_isActive(isActive){}
	void SetIsActive(bool isActive){m_isActive = isActive;}
	bool IsActive(){return m_isActive;}
	void DecrementLifeSpan(ParticleBatch& particleBatch);
private:
	bool m_isActive;
};

}
}

#endif