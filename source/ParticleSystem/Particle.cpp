#include "ParticleSystem/Particle.h"

namespace Atum
{
namespace ParticleSystem
{

//-------------------------------
Particle::Particle(ParticleParams params)
	: m_params(params)
{
	m_params.isAlive = false;
}

//-------------------------------
Particle::~Particle(void)
{
}

}
}
