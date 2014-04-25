#include "ParticleSystem/Behavior/ExplodingSizeBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{

void ExplodingSizeBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	if(particleBatch.GetInitialLifeSpan()>0.001f)
	{
		particleBatch.SetAlphaSize(1.0-particleBatch.GetLifeSpan()/particleBatch.GetInitialLifeSpan());
	}
}
}
}