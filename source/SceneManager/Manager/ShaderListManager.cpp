#include <bitset>

#include "ShaderListManager.h"

#include "Utilities/IdGenerator/IdGenerator.h"

namespace Atum
{
namespace SceneManager
{

//-----------------------------------------------------------------------------
ShaderListManager::ShaderListManager()
{}

//-----------------------------------------------------------------------------
ShaderListManager::~ShaderListManager()
{
	ClearAll();
}

//-----------------------------------------------------------------------------
Atum::SceneManager::ShaderListID ShaderListManager::CreateShaderList( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::bitset<MATERIALEFFECT_COUNT> shaderCompileFlags)
{
	// Create the arguments for compilation from the flag list
	int currentNumberArguments = 0; // we start at 1 because the first array is filled with the shader code
	std::string argumentList;
	std::string shaderCompileFlagsString = shaderCompileFlags.to_string();

	for(int i = 0; i < MATERIALEFFECT_COUNT; i++)
	{
		// If the flag is set to 1, than it means the compilation macro is activated
		if(shaderCompileFlagsString[i] == '1')
		{
			argumentList += "#define ";
			argumentList += MaterialEffectsName[i];
			argumentList += '\n';
		}
	}

	ShaderList* shaderList = new ShaderList( vertexShaderFileName, fragmentShaderFileName, argumentList );
	ShaderListID id = InsertShaderList( shaderList );
	m_shaderVariationMap[shaderCompileFlags.to_ullong()] = id;
	return id;
}

//-----------------------------------------------------------------------------
void ShaderListManager::RemoveShaderList( ShaderListID shaderListID )
{
	ShaderListMap::iterator it ( m_shaderListMap.find(shaderListID) );
	if ( it != m_shaderListMap.end() ) //id exists!
	{
		delete (*it).second;
		m_shaderListMap.erase(it);
	}
}

//-----------------------------------------------------------------------------
ShaderList* const ShaderListManager::GetShaderList( ShaderListID shaderListID )
{
	if ( m_shaderListMap.find(shaderListID) != m_shaderListMap.end() ) //id exists!
	{
		return m_shaderListMap[shaderListID];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
ShaderListID ShaderListManager::InsertShaderList( ShaderList* const shaderList )
{
	ShaderListID id = Utilities::IdGenerator::GetInstance().GenerateId();
	m_shaderListMap[id] = shaderList;
	return id;
}

//-----------------------------------------------------------------------------
void ShaderListManager::ClearAll()
{
	ShaderListMap::iterator it(m_shaderListMap.begin());
	for(; it != m_shaderListMap.end(); it++)
	{
		delete (*it).second;
	}
	m_shaderListMap.clear();
}

//-----------------------------------------------------------------------------
Atum::SceneManager::ShaderListID ShaderListManager::GetShaderListIdFromFlags( std::bitset<MATERIALEFFECT_COUNT> flags )
{
	unsigned long int flagsUL = flags.to_ullong();
	if ( m_shaderVariationMap.find(flagsUL) != m_shaderVariationMap.end() ) //id exists!
	{
		return m_shaderVariationMap[flagsUL];
	}
	else
	{
		return 0;
	}
}


}
}
