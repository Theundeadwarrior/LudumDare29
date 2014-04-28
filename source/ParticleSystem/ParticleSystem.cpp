#include "ParticleSystem/ParticleSystem.h"
#include "Utilities/Math/MathUtilities.h"
#include "Utilities/Physic/AABB.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Properties/Property.h"
#include "SceneManager/Properties/PropertyList.h"

namespace Atum
{
namespace ParticleSystem
{

//-------------------------------
ParticleSystem::ParticleSystem(const ParticleSystemParameters& parameters, unsigned int nbParticleMax, unsigned int nbTargetParticle, unsigned int nbParticleBatches)
	: m_parameters(parameters),
	m_spawner(nbTargetParticle, m_parameters)
{
	m_particleBatches.reserve(nbParticleBatches);
	for(unsigned int i = 0; i < nbParticleBatches; ++i)
	{
		m_particleBatches.push_back(ParticleBatch(nbParticleMax/nbParticleBatches+1));
		m_spawner.ResetParticleBatch(m_particleBatches[i], i);
	}
	
	Reset();

	if(parameters.lifespanRange[0] > 0.001f || parameters.lifespanRange[1] > 0.001f)
	{
		m_despawner = Despawner(true);
	}
	UpdateAABB();
	m_name = "Particle System";
}

//-------------------------------
ParticleSystem::~ParticleSystem(void)
{
	for(unsigned int i = 0; i < m_parameters.behaviors.size(); ++i)
	{
		delete m_parameters.behaviors[i];
	}
	m_parameters.behaviors.clear();
}

//-------------------------------
void ParticleSystem::Draw()
{
	SceneManager::ShaderList* shaderList = GetShaderList();
	LowLevelGraphics::LowLevelAPI::BindShaders(shaderList);

	glm::vec4 rangeBoundColor = m_parameters.colorRange[1]-m_parameters.colorRange[0];
	float rangeBoundSize = m_parameters.particleSizeRange[1]-m_parameters.particleSizeRange[0];

	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("LowerBoundColor", &m_parameters.colorRange[0], SHADER_FLOAT4);
	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("RangeBoundColor", &rangeBoundColor, SHADER_FLOAT4);
	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("LowerBoundSize", &m_parameters.particleSizeRange[0], SHADER_FLOAT);
	shaderList->GetShaderProgram()->UpdateShaderParameterWithName("RangeBoundSize", &rangeBoundSize, SHADER_FLOAT);

	for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
	{
		if(m_despawner.IsActive() && m_particleBatches[i].GetLifeSpan() <= 0.0f)
		{
			m_spawner.ResetParticleBatch(m_particleBatches[i],i);
		}
	}

	m_spawner.Update(m_particleBatches);

	for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
	{
		for(unsigned int j = 0; j < m_parameters.behaviors.size(); ++j)
		{
			m_parameters.behaviors[j]->Update(m_particleBatches[i],i);
		}

		m_particleBatches[i].Update();
		m_particleBatches[i].Draw(shaderList);

		m_despawner.DecrementLifeSpan(m_particleBatches[i]);
	}

	LowLevelGraphics::LowLevelAPI::UnbindShaders();
}

//-------------------------------
void ParticleSystem::Reset()
{
	for(unsigned int i=0; i<m_particleBatches.size(); ++i)
	{
		m_particleBatches[i].Reset();
	}
	m_parameters.nbAlive = 0;
}

//-------------------------------
void ParticleSystem::UpdateAABB()
{
	float maxOneOrRadius = glm::max(1.0f, m_parameters.offsetRadius);
	glm::vec3 minBounds(m_parameters.emitPosition.x - maxOneOrRadius,
						m_parameters.emitPosition.y - maxOneOrRadius,
						m_parameters.emitPosition.z - maxOneOrRadius);
	glm::vec3 maxBounds(m_parameters.emitPosition.x + maxOneOrRadius,
						m_parameters.emitPosition.y + maxOneOrRadius,
						m_parameters.emitPosition.z + maxOneOrRadius);

	m_aabb = Utilities::AABB(minBounds, maxBounds);
}

//-------------------------------
SceneManager::ShaderList* const ParticleSystem::GetShaderList()
{
	return SceneManager::SceneManager::GetInstance().GetShaderListManager()->GetShaderList(m_parameters.shaderListID);
}

//-------------------------------
void ParticleSystem::GetPropertyList( SceneManager::PropertyList& o_properties ) const
{
	SceneManager::Property* name = new SceneManager::Property( COMP_PROP_NAME, GetName() );
	o_properties.AddProperty(name);

	SceneManager::Property* position = new SceneManager::Property( COMP_PROP_POSITION, m_parameters.emitPosition );
	o_properties.AddProperty(position);

	SceneManager::Property* scale = new SceneManager::Property( COMP_PROP_SCALE, m_parameters.offsetRadius );
	o_properties.AddProperty(scale);

	SceneManager::Property* targetParticles = new SceneManager::Property( "Target Nb Particles", (int)(m_spawner.GetTargetNbParticle()) );
	o_properties.AddProperty(targetParticles);

	SceneManager::Property* orientationLower = new SceneManager::Property( "Lower Bound Orientation", glm::vec3(m_parameters.orientationRange[0]));
	o_properties.AddProperty(orientationLower);

	SceneManager::Property* orientationUpper = new SceneManager::Property( "Upper Bound Orientation", glm::vec3(m_parameters.orientationRange[1]));
	o_properties.AddProperty(orientationUpper);

	SceneManager::Property* colorLower = new SceneManager::Property( "Lower Bound Color", glm::vec3(m_parameters.colorRange[0]), SceneManager::VECTORTYPE_COLOR);
	o_properties.AddProperty(colorLower);

	SceneManager::Property* colorUpper = new SceneManager::Property( "Upper Bound Color", glm::vec3(m_parameters.colorRange[1]), SceneManager::VECTORTYPE_COLOR);
	o_properties.AddProperty(colorUpper);

	SceneManager::Property* alphaLower = new SceneManager::Property( "Lower Bound Alpha", m_parameters.colorRange[0].a);
	o_properties.AddProperty(alphaLower);

	SceneManager::Property* alphaUpper = new SceneManager::Property( "Upper Bound Alpha", m_parameters.colorRange[1].a);
	o_properties.AddProperty(alphaUpper);

	SceneManager::Property* sizeLower = new SceneManager::Property( "Lower Bound Size", m_parameters.particleSizeRange[0]);
	o_properties.AddProperty(sizeLower);

	SceneManager::Property* sizeUpper = new SceneManager::Property( "Upper Bound Size", m_parameters.particleSizeRange[1]);
	o_properties.AddProperty(sizeUpper);

	SceneManager::Property* lifespanLower = new SceneManager::Property( "Lower Bound LifeSpan", m_parameters.lifespanRange[0]);
	o_properties.AddProperty(lifespanLower);

	SceneManager::Property* lifespanUpper = new SceneManager::Property( "Upper Bound LifeSpan", m_parameters.lifespanRange[1]);
	o_properties.AddProperty(lifespanUpper);

	SceneManager::Property* velocityLower = new SceneManager::Property( "Lower Bound Velocity", m_parameters.velocityRange[0]);
	o_properties.AddProperty(velocityLower);

	SceneManager::Property* velocityUpper = new SceneManager::Property( "Upper Bound Velocity", m_parameters.velocityRange[1]);
	o_properties.AddProperty(velocityUpper);
}

//-------------------------------
void ParticleSystem::UpdatePropertyList( const SceneManager::PropertyList& i_properties )
{
	const SceneManager::Property* name = i_properties.GetProperty(COMP_PROP_NAME);
	if ( name )
	{
		name->GetValue(m_name);
	}
	const SceneManager::Property* position = i_properties.GetProperty(COMP_PROP_POSITION);
	if ( position )
	{
		position->GetValue(m_parameters.emitPosition);
		UpdateAABB();
	}
	const SceneManager::Property* scale = i_properties.GetProperty(COMP_PROP_SCALE);
	if ( scale )
	{
		scale->GetValue(m_parameters.offsetRadius);
		UpdateAABB();
	}

	const SceneManager::Property* targetParticles = i_properties.GetProperty("Target Nb Particles");
	if ( targetParticles )
	{
		int iTargetParticles;
		targetParticles->GetValue(iTargetParticles);
		m_spawner.SetTargetNbParticle((unsigned int)glm::max(0,iTargetParticles));
	}

	const SceneManager::Property* orientationLower = i_properties.GetProperty("Lower Bound Orientation");
	if ( orientationLower )
	{
		orientationLower->GetValue(m_parameters.orientationRange[0]);
	}

	const SceneManager::Property* orientationUpper = i_properties.GetProperty("Upper Bound Orientation");
	if ( orientationUpper )
	{
		orientationUpper->GetValue(m_parameters.orientationRange[1]);
	}

	const SceneManager::Property* colorLower = i_properties.GetProperty("Lower Bound Color");
	if ( colorLower )
	{
		glm::vec3 color;
		colorLower->GetValue(color);
		m_parameters.colorRange[0] = glm::vec4(color,m_parameters.colorRange[0].a);
	}

	const SceneManager::Property* colorUpper = i_properties.GetProperty("Upper Bound Color");
	if ( colorLower )
	{
		glm::vec3 color;
		colorUpper->GetValue(color);
		m_parameters.colorRange[1] = glm::vec4(color,m_parameters.colorRange[1].a);
	}

	const SceneManager::Property* alphaLower = i_properties.GetProperty("Lower Bound Alpha");
	if ( alphaLower )
	{
		alphaLower->GetValue(m_parameters.colorRange[0].a);
	}

	const SceneManager::Property* alphaUpper = i_properties.GetProperty("Upper Bound Alpha");
	if ( alphaUpper )
	{
		alphaUpper->GetValue(m_parameters.colorRange[1].a);
	}

	const SceneManager::Property* sizeLower = i_properties.GetProperty("Lower Bound Size");
	if ( sizeLower )
	{
		sizeLower->GetValue(m_parameters.particleSizeRange[0]);
	}

	const SceneManager::Property* sizeUpper = i_properties.GetProperty("Upper Bound Size");
	if ( sizeUpper )
	{
		sizeUpper->GetValue(m_parameters.particleSizeRange[1]);
	}

	const SceneManager::Property* lifespanLower = i_properties.GetProperty("Lower Bound LifeSpan");
	if ( lifespanLower )
	{
		lifespanLower->GetValue(m_parameters.lifespanRange[0]);
		for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
		{
			m_particleBatches[i].SetLifeSpan(Utilities::UniformProbability(m_parameters.lifespanRange[0], m_parameters.lifespanRange[1]));
			m_particleBatches[i].SetInitialLifeSpan(m_particleBatches[i].GetLifeSpan());
		}
	}

	const SceneManager::Property* lifespanUpper = i_properties.GetProperty("Upper Bound LifeSpan");
	if ( lifespanUpper )
	{
		lifespanUpper->GetValue(m_parameters.lifespanRange[1]);
		for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
		{
			m_particleBatches[i].SetLifeSpan(Utilities::UniformProbability(m_parameters.lifespanRange[0], m_parameters.lifespanRange[1]));
			m_particleBatches[i].SetInitialLifeSpan(m_particleBatches[i].GetLifeSpan());
		}
	}

	const SceneManager::Property* velocityLower = i_properties.GetProperty("Lower Bound Velocity");
	if ( velocityLower )
	{
		velocityLower->GetValue(m_parameters.velocityRange[0]);
		for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
		{
			m_particleBatches[i].SetVelocity(Utilities::UniformProbability(m_parameters.velocityRange[0], m_parameters.velocityRange[1]));
		}
	}

	const SceneManager::Property* velocityUpper = i_properties.GetProperty("Upper Bound Velocity");
	if ( velocityUpper )
	{
		velocityUpper->GetValue(m_parameters.velocityRange[1]);
		for(unsigned int i = 0; i < m_particleBatches.size(); ++i)
		{
			m_particleBatches[i].SetVelocity(Utilities::UniformProbability(m_parameters.velocityRange[0], m_parameters.velocityRange[1]));
		}
	}
}

void ParticleSystem::SetColor(glm::vec4 minColor, glm::vec4 maxColor)
{
	m_parameters.colorRange[0] = minColor;
	m_parameters.colorRange[1] = maxColor;
}

}
}
