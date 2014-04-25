#ifndef PARTICLESYSTEM_PARTICLESYSTEM_H
#define PARTICLESYSTEM_PARTICLESYSTEM_H

#include <vector>
#include "GLM/include/glm/glm.hpp"
#include "ParticleSystem/Behavior/Behavior.h"
#include "SceneManager/Manager/TypedefID.h"
#include "Utilities/Physic/AABB.h"
#include "ParticleSystem/ParticleBatch.h"
#include "ParticleSystem/Spawner/Spawner.h"
#include "ParticleSystem/Spawner/Despawner.h"
#include "SceneManager/Component/Component.h"

namespace Atum
{
namespace SceneManager
{
class ShaderList;
class PropertyList; 
}
namespace ParticleSystem
{

class ParticleSystemParameters
{
public:
	ParticleSystemParameters():offsetRadius(0.0), nbAlive(0) {lifespanRange[0] = 0.0f; lifespanRange[1] = 0.0f;}

	std::vector<Behavior*> behaviors;

	glm::vec4 colorRange[2];

	glm::vec3 emitPosition;
	glm::vec3 orientationRange[2];

	float offsetRadius;
	float lifespanRange[2];
	float particleSizeRange[2];
	float velocityRange[2];

	unsigned int nbAlive;

	SceneManager::ShaderListID shaderListID;
};

class ParticleSystem : public SceneManager::Component
{
public:
	ParticleSystem(const ParticleSystemParameters& parameters, unsigned int nbParticleMax, unsigned int nbTargetParticle, unsigned int nbParticleBatches);
	~ParticleSystem(void);

	void Reset();
	void Draw();

	void SetPosition(glm::vec3 position){m_parameters.emitPosition = position;}

	glm::vec3 GetPosition()const{return m_parameters.emitPosition;}
	Spawner GetSpawner(){return m_spawner;}
	SceneManager::ShaderList* const GetShaderList();
	std::vector<ParticleBatch>::const_iterator GetParticleBatchListBegin()const{return m_particleBatches.begin();}
	std::vector<ParticleBatch>::const_iterator GetParticleBatchListEnd()const{return m_particleBatches.end();}

	void GetPropertyList ( SceneManager::PropertyList& o_properties ) const;
	void UpdatePropertyList ( const SceneManager::PropertyList& i_properties );

	void UpdateAABB();

private:
	std::vector<ParticleBatch> m_particleBatches;
	ParticleSystemParameters m_parameters;
	Spawner m_spawner;
	Despawner m_despawner;
};

}
}

#endif
