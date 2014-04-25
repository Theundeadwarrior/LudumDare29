#include "ParticleSystem/Spawner/Spawner.h"
#include "ParticleSystem/ParticleSystem.h"
#include "Utilities/Math/MathUtilities.h"
#include "ParticleSystem/ParticleBatch.h"

namespace Atum
{
	namespace ParticleSystem
	{

		Spawner::Spawner(int targetNbParticle, ParticleSystemParameters& sysParams)
			:m_targetNbParticle(targetNbParticle),
			m_isActive(true),
			m_sysParams(sysParams)
		{

		}

		Spawner::~Spawner(void)
		{
		}

		void Spawner::ResetParticleBatch(ParticleBatch& particleBatch, unsigned int index)
		{
			if(m_isActive)
			{
				m_sysParams.nbAlive -= particleBatch.GetNbAlive();
				particleBatch.Reset();
				particleBatch.SetVelocity(Utilities::UniformProbability(m_sysParams.velocityRange[0], m_sysParams.velocityRange[1]));
				particleBatch.SetAlphaColor(glm::vec4(Utilities::UniformProbability(0.0f, 1.0f),
														Utilities::UniformProbability(0.0f, 1.0f),
														Utilities::UniformProbability(0.0f, 1.0f),
														Utilities::UniformProbability(0.0f, 1.0f)));
				particleBatch.SetAlphaSize(Utilities::UniformProbability(0.0f, 1.0f));
				particleBatch.SetLifeSpan(Utilities::UniformProbability(m_sysParams.lifespanRange[0],m_sysParams.lifespanRange[1]));
				particleBatch.SetInitialLifeSpan(particleBatch.GetLifeSpan());

				for(unsigned int i = 0; i < m_sysParams.behaviors.size(); i++)
				{
					m_sysParams.behaviors[i]->CreateParticleBatchProperty(index);
				}
			}
		}

		void Spawner::ResetParticle(Particle& particle)
		{
			float length = Utilities::UniformProbability(0.0f, m_sysParams.offsetRadius);
			particle.SetOrientation(glm::vec3(Utilities::UniformProbability(m_sysParams.orientationRange[0].x, m_sysParams.orientationRange[1].x),
												Utilities::UniformProbability(m_sysParams.orientationRange[0].y, m_sysParams.orientationRange[1].y),
												Utilities::UniformProbability(m_sysParams.orientationRange[0].z, m_sysParams.orientationRange[1].z)));
			particle.SetPosition(m_sysParams.emitPosition + particle.GetOrientation()*length);
			particle.SetIsAlive(true);
			particle.SetLifespan(Utilities::UniformProbability(m_sysParams.lifespanRange[0],m_sysParams.lifespanRange[1]));

			m_sysParams.nbAlive++;
		}

		void Spawner::Update(std::vector<ParticleBatch>& particleBatches)
		{
			if(m_isActive && m_sysParams.nbAlive < m_targetNbParticle)
			{
				if(particleBatches.size()>1)
				{
					unsigned int smallestParticleBatchIndex = 0;
					unsigned int secondSmallestParticleBatchIndex = particleBatches.size()-1;

					for(unsigned int i = 1; i < particleBatches.size(); ++i)
					{
						if(particleBatches[i].GetNbAlive() <= particleBatches[smallestParticleBatchIndex].GetNbAlive())
						{
							secondSmallestParticleBatchIndex = smallestParticleBatchIndex;
							smallestParticleBatchIndex = i;
						}
					}

					unsigned int nbDifferenceNbAlive = particleBatches[secondSmallestParticleBatchIndex].GetNbAlive() - particleBatches[smallestParticleBatchIndex].GetNbAlive()+MIN_SPAWN_PARTICLES_RATIO*m_targetNbParticle;

					std::vector<Particle>::iterator it = particleBatches[smallestParticleBatchIndex].GetParticleListBegin();
					std::vector<Particle>::iterator itEnd = particleBatches[smallestParticleBatchIndex].GetParticleListEnd();

					for(; it!=itEnd; ++it)
					{
						if(!it->IsAlive())
						{
							ResetParticle(*it);
							particleBatches[smallestParticleBatchIndex].IncrementNbAlive();
							if(nbDifferenceNbAlive)
							{
								nbDifferenceNbAlive--;
							}
							else
							{
								Update(particleBatches);
							}
							if(m_sysParams.nbAlive >= m_targetNbParticle)
							{
								return;
							}
						}
					}
				}
				else
				{
					std::vector<Particle>::iterator it = particleBatches[0].GetParticleListBegin();
					std::vector<Particle>::iterator itEnd = particleBatches[0].GetParticleListEnd();

					for(; it!=itEnd; ++it)
					{
						if(!it->IsAlive())
						{
							ResetParticle(*it);

							if(m_sysParams.nbAlive >= m_targetNbParticle)
							{
								return;
							}
						}
					}
				}
			}
		}

		void Spawner::Burst(std::vector<ParticleBatch>& particles)
		{

		}
	}
}