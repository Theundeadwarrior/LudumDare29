#include "ParticleSystem/Behavior/MultiColorBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"
#include "Utilities/Math/MathUtilities.h"

namespace Atum
{
namespace ParticleSystem
{
void MultiColorBehavior::CreateParticleBatchProperty( unsigned int index)
{
	if(index > m_particleBatchMultiColor.size())
	{
		m_particleBatchMultiColor.resize(index+10);
	}
	m_particleBatchMultiColor[index] = glm::vec3(Utilities::UniformProbability(0.0f, 1.0f),
													Utilities::UniformProbability(0.0f, 1.0f),
													Utilities::UniformProbability(0.0f, 1.0f));
}

void MultiColorBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	if(particleBatch.GetInitialLifeSpan()>0.001f)
	{
		if(index > m_particleBatchMultiColor.size())
		{
			CreateParticleBatchProperty(index);
		}
		glm::vec3 lapOffset = glm::vec3(Utilities::UniformProbability(0.0f, 1.0f),
										Utilities::UniformProbability(0.0f, 1.0f),
										Utilities::UniformProbability(0.0f, 1.0f));

		m_particleBatchMultiColor[index] += lapOffset*Utilities::Timer::GetInstance()->GetLapTime()/particleBatch.GetInitialLifeSpan();
		particleBatch.SetAlphaColor(glm::vec4(m_particleBatchMultiColor[index].r,m_particleBatchMultiColor[index].g,m_particleBatchMultiColor[index].b,particleBatch.GetAlphaColor().a));
	}
}
}
}