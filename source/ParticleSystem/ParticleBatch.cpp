#include "ParticleSystem/ParticleBatch.h"
#include "SceneManager/Manager/ShaderListManager.h"
#include "Utilities/Timer/Timer.h"

namespace Atum
{
namespace ParticleSystem
{

//-------------------------------
ParticleBatch::ParticleBatch(ParticleBatchParams params, unsigned int nbParticles)
	: m_params(params)
{
	m_particles.resize(nbParticles);
}

//-------------------------------
ParticleBatch::~ParticleBatch(void)
{
}

//-------------------------------
void ParticleBatch::Draw(SceneManager::ShaderList* const shaderList)const
{
	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("AlphaSize", &m_params.alphaSize, SHADER_FLOAT);
	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("AlphaColor", &m_params.alphaColor, SHADER_FLOAT4);

	LowLevelGraphics::LowLevelAPI::DrawCallParticles(m_particles);
}

//-------------------------------
void ParticleBatch::Reset()
{
	for(unsigned int i=0; i<m_particles.size(); ++i)
	{
		m_particles[i].SetIsAlive(false);
	}
	m_params.nbAlive = 0;
}

//-------------------------------
void ParticleBatch::Update()
{
	for(unsigned int i=0; i<m_particles.size(); ++i)
	{
		if(m_particles[i].IsAlive())
		{
			m_particles[i].SetPosition(m_particles[i].GetPosition() + m_particles[i].GetOrientation()*Utilities::Timer::GetInstance()->GetLapTime() * m_params.velocity);
		}
	}
}

}
}
