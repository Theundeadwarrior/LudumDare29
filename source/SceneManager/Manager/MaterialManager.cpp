#include "MaterialManager.h"
#include "Utilities/IdGenerator/IdGenerator.h"
#include "SceneManager/Material/Material.h"

namespace Atum
{
namespace SceneManager
{

std::vector<std::pair<int,std::string>> MaterialManager::m_materialEffectList;
//-----------------------------------------------------------------------------
MaterialManager::MaterialManager()
{
	m_materialEffectList.resize(2);
	m_materialEffectList[0] = (std::pair<int,std::string>(0, "PLAIN_COLOR"));
	m_materialEffectList[1] = (std::pair<int,std::string>(1, "PHONG"));
}

//-----------------------------------------------------------------------------
MaterialManager::~MaterialManager()
{
	ClearAll();
}

//-----------------------------------------------------------------------------
MaterialID MaterialManager::CreateMaterial(MaterialParameters materialParameters, ShaderListID shaderListId)
{
	Material* material = new Material(materialParameters, shaderListId);
	return InsertMaterial( material );
}

//-----------------------------------------------------------------------------
Atum::SceneManager::MaterialID MaterialManager::CreateMaterial(ShaderListID shaderListId)
{
	Material* material = new Material(shaderListId);
	return InsertMaterial( material );
}

//-----------------------------------------------------------------------------
void MaterialManager::RemoveMaterial( MaterialID materialID )
{
	MaterialMap::iterator it ( m_materialMap.find(materialID) );
	if ( it != m_materialMap.end() ) //id exists!
	{
		delete (*it).second;
		m_materialMap.erase(it);
	}
}

//-----------------------------------------------------------------------------
Material* const MaterialManager::GetMaterial( MaterialID id )
{
	if ( m_materialMap.find(id) != m_materialMap.end() ) //id exists!
	{
		return m_materialMap[id];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
MaterialID MaterialManager::InsertMaterial( Material* const material )
{
	MaterialID id = Utilities::IdGenerator::GetInstance().GenerateId();
	m_materialMap[id] = material;
	return id;
}

//-----------------------------------------------------------------------------
void MaterialManager::ClearAll()
{
	MaterialMap::iterator it(m_materialMap.begin());
	for(; it != m_materialMap.end(); it++)
	{
		delete (*it).second;
	}
	m_materialMap.clear();
}

std::vector<std::pair<int,std::string>>* MaterialManager::GetLightingTechniques()
{
	return &m_materialEffectList;
}

/*
void MaterialManager::InsertMaterialWithId( Material* const material, MaterialID materialID )
{
	m_materialMap[materialID] = material;
}*/

}
}