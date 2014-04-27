#include "SceneManager.h"
#include "Utilities/Debug/Debug.h"

#include "SceneManager/Scene/Scene.h"

namespace Atum
{
namespace SceneManager
{


SceneManager::SceneManager()
: m_currentScene(NULL)
{


}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

SceneManager::~SceneManager()
{
	ClearAllScenes();
}

MaterialManager* const SceneManager::GetMaterialManager() 
{
	return &m_materialManager;
}

ShaderListManager* const SceneManager::GetShaderListManager() 
{
	return &m_shaderListManager;
}

GeometryManager* const SceneManager::GetGeometryManager() 
{
	return &m_geometryManager;
}

TextureManager* const SceneManager::GetTextureManager() 
{
    return &m_textureManager;
}

Scene* SceneManager::GetCurrentScene()
{
	ATUM_ASSERT_MESSAGE(m_currentScene, "There are no current scene. Please use SetCurrentScene.");
	return m_currentScene;	
}

void SceneManager::UpdateCurrentScene()
{
	m_currentScene->Update();
}

void SceneManager::ClearAllResources()
{
	m_geometryManager.ClearAll();
	m_materialManager.ClearAll();
	m_shaderListManager.ClearAll();
	m_textureManager.ClearAll();
	ClearAllScenes();
}

void SceneManager::ClearAllScenes()
{
	m_currentScene = NULL;
	m_sceneList.clear();
}

} // namespace SceneManager
} // namespace Atum
