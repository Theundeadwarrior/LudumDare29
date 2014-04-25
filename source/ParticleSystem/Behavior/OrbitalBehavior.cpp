#include "ParticleSystem/Behavior/OrbitalBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{

void OrbitalBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	std::vector<Particle>::iterator it = particleBatch.GetParticleListBegin();
	std::vector<Particle>::iterator itEnd = particleBatch.GetParticleListEnd();
	for(; it != itEnd; ++it)
	{
		if(it->IsAlive())
		{
			glm::vec3 attractionForce = glm::vec3(0.0f,0.0f,0.0f);
			for(unsigned int i=0; i<m_centers.size(); i++)
			{
				glm::vec3 between = m_centers[i].position - it->GetPosition();
				float norm = glm::dot(between,between);

				if(norm > 100.0f)
					norm = 100.0f;
				else if(norm < 50.0f)
					norm = 50.0f;

				float mult = (66.27428f/norm)*m_centers[i].force;
				attractionForce = attractionForce + (mult * glm::normalize(between));
				attractionForce *= 0.1f;
				glm::vec3 speed = (particleBatch.GetVelocity() * it->GetOrientation()) + (Utilities::Timer::GetInstance()->GetLapTime() * attractionForce);

				it->SetOrientation(speed);
			}
		}
	}
}
}
}
