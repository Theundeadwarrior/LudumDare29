#ifndef PARTICLESYSTEM_PARTICLEBATCH_H
#define PARTICLESYSTEM_PARTICLEBATCH_H

#include <vector>
#include "ParticleSystem/Particle.h"

namespace Atum
{
namespace SceneManager{class ShaderList;}
namespace ParticleSystem
{

struct ParticleBatchParams
{
	unsigned int nbAlive;
	float initialLifespan;
	float lifespan;
	float velocity;
	float alphaSize;
	glm::vec4 alphaColor;
};

class ParticleBatch
{
public:
	friend class ParticleSystem;
	friend class Spawner;

	~ParticleBatch(void);

	void SetVelocity(float velocity){m_params.velocity = velocity;}
	void SetAlphaColor(glm::vec4 alpha){m_params.alphaColor = alpha;}
	void SetAlphaSize(float alpha){m_params.alphaSize = alpha;}
	void SetLifeSpan(float lifespan){m_params.lifespan = lifespan;}
	void SetInitialLifeSpan(float lifespan){m_params.initialLifespan = lifespan;}

	unsigned int GetNbAlive(){return m_params.nbAlive;}
	float GetVelocity() const{return m_params.velocity;}
	glm::vec4 GetAlphaColor(){return m_params.alphaColor;}
	float GetLifeSpan()const{return m_params.lifespan;}
	float GetInitialLifeSpan()const{return m_params.initialLifespan;}

	void IncrementNbAlive(){m_params.nbAlive++;}
	void DecrementNbAlive(){if(m_params.nbAlive>0){m_params.nbAlive--;}}

	std::vector<Particle>::iterator GetParticleListBegin(){return m_particles.begin();}
	std::vector<Particle>::iterator GetParticleListEnd(){return m_particles.end();}

private:
	ParticleBatch(unsigned int nbParticles){m_particles.resize(nbParticles);}
	ParticleBatch(ParticleBatchParams params, unsigned int nbParticles);

	void Draw(SceneManager::ShaderList* const shaderList)const;
	void Reset();
	void Update();

	std::vector<Particle> m_particles;
	ParticleBatchParams m_params;
};

}
}

#endif
