#include "ParticleSystem/Behavior/AccelerationBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"
#include "Utilities/Math/MathUtilities.h"

namespace Atum
{
namespace ParticleSystem
{

AccelerationBehavior::AccelerationBehavior(float minA, float maxA, unsigned int nbParticleBatches)
:m_minAcceleration(minA)
,m_maxAcceleration(maxA)
{
	m_particleBatchAccelerations.resize(nbParticleBatches);
}

void AccelerationBehavior::CreateParticleBatchProperty( unsigned int index)
{
	if(index > m_particleBatchAccelerations.size())
	{
		m_particleBatchAccelerations.resize(index+10);
	}
	m_particleBatchAccelerations[index] = Utilities::UniformProbability(m_minAcceleration, m_maxAcceleration);
}

void AccelerationBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	if(index > m_particleBatchAccelerations.size())
	{
		CreateParticleBatchProperty(index);
	}
	particleBatch.SetVelocity(particleBatch.GetVelocity() + Utilities::Timer::GetInstance()->GetLapTime() * m_particleBatchAccelerations[index]*0.5f);
}

}
}
