#include "ParticleSystem/Spawner/Despawner.h"

#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{
void Despawner::DecrementLifeSpan(ParticleBatch& particleBatch)
{
	if(m_isActive && particleBatch.GetLifeSpan() > 0.0f)
	{
		particleBatch.SetLifeSpan(particleBatch.GetLifeSpan()-Utilities::Timer::GetInstance()->GetLapTime());

		std::vector<Particle>::iterator it = particleBatch.GetParticleListBegin();
		std::vector<Particle>::iterator itEnd = particleBatch.GetParticleListEnd();

		for(;it!=itEnd;++it)
		{
			if(it->IsAlive())
			{
				it->SetLifespan(it->GetLifeSpan()-Utilities::Timer::GetInstance()->GetLapTime());
				if(it->GetLifeSpan() < 0.0f)
				{
					it->SetIsAlive(false);
				}
			}
		}
	}
}
}
}