#ifndef PARTICLESYSTEM_SPAWNER_H
#define PARTICLESYSTEM_SPAWNER_H

#include <vector>

#define MIN_SPAWN_PARTICLES_RATIO 0.0005f

namespace Atum
{
	namespace ParticleSystem
	{
		class Particle;
		class ParticleBatch;
		class ParticleSystemParameters;

		class Spawner
		{
		public:
			Spawner(int targetNbParticle, ParticleSystemParameters& sysParams);
			~Spawner(void);
			void Update(std::vector<ParticleBatch>& particles);
			void ResetParticleBatch(ParticleBatch& particleBatch, unsigned int index);
			void Burst(std::vector<ParticleBatch>& particles);

			unsigned int GetTargetNbParticle()const{return m_targetNbParticle;}

			void SetTargetNbParticle(unsigned int nbParticle){m_targetNbParticle = nbParticle;}
			void SetIsActive(bool isActive){m_isActive=isActive;}

		private:
			void ResetParticle(Particle& particle);

			unsigned int m_targetNbParticle;
			bool m_isActive;
			ParticleSystemParameters& m_sysParams;
		};

	}
}

#endif