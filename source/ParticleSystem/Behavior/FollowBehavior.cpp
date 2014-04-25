#include "ParticleSystem/Behavior/FollowBehavior.h"
#include "ParticleSystem/ParticleBatch.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{
void FollowBehavior::Update(ParticleBatch& particleBatch, unsigned int index)
{
	std::vector<Particle>::iterator it = particleBatch.GetParticleListBegin();
	std::vector<Particle>::iterator itEnd = particleBatch.GetParticleListEnd();

	while(it != itEnd && !it->IsAlive())
	{
		++it;
	}
	if(it != itEnd)
	{
		//For the leader
		glm::vec3 oldPos = it->GetPosition();
		glm::vec3 attractionForce = glm::vec3(0.0f,0.0f,0.0f);
		for(unsigned int i=0; i<m_centers.size(); ++i)
		{
			glm::vec3 between = m_centers[i].position - oldPos;
			float norm = glm::dot(between,between);

			if(norm < 20)
				norm = 20;
			else if(norm > 150)
				norm = 150;

			float mult = (662.7428f/norm)*m_centers[i].force;
			attractionForce += (mult * glm::normalize(between));
		}
		attractionForce *= 0.1f;
		glm::vec3 speed = particleBatch.GetVelocity() * it->GetOrientation() + (Utilities::Timer::GetInstance()->GetLapTime() * attractionForce);
		it->SetOrientation(speed);
		++it;

		//For all the others
		for(; it != itEnd; ++it)
		{
			if(it->IsAlive())
			{
				it->SetOrientation(oldPos-it->GetPosition());
				oldPos = it->GetPosition();
			}
		}
	}
}
}
}