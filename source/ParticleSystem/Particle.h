#ifndef PARTICLESYSTEM_PARTICLE_H
#define PARTICLESYSTEM_PARTICLE_H

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace ParticleSystem
{

struct ParticleParams
{
	glm::vec3 position;
	glm::vec3 orientation;
	float lifespan;
	bool isAlive;
};

class Particle
{
public:
	Particle(){m_params.isAlive = false;}
	Particle(ParticleParams params);
	~Particle(void);

	void SetPosition(glm::vec3& pos){ m_params.position = pos;}
	void SetOrientation(glm::vec3& orientation){ m_params.orientation = glm::normalize(orientation);}
	void SetIsAlive(bool isAlive){m_params.isAlive = isAlive;}
	void SetLifespan(float lifespan){m_params.lifespan = lifespan;}

	const glm::vec3& GetPosition() const{return m_params.position;}
	const glm::vec3& GetOrientation() const{return m_params.orientation;}
	float GetLifeSpan()const{return m_params.lifespan;}
	bool IsAlive()const{return m_params.isAlive;}

private:
	ParticleParams m_params;
};

}
}

#endif
