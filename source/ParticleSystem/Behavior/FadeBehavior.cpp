#include "ParticleSystem/Behavior/FadeBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{
void FadeBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	if(particleBatch.GetInitialLifeSpan()>0.001f)
	{
		particleBatch.SetAlphaColor(glm::vec4(particleBatch.GetAlphaColor().r,particleBatch.GetAlphaColor().g,particleBatch.GetAlphaColor().b,particleBatch.GetLifeSpan()/particleBatch.GetInitialLifeSpan()));
	}
}
}
}