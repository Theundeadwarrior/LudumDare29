#include "SceneManager.h"
#include "Utilities/Debug/Debug.h"
#include "SceneManager/Level/Level.h"
#include "SceneManager/Objects/GameplayObjects/Platform.h"

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


void SceneManager::CreateSceneFromLevel(Scene* outCreatedScene, const Level& level)
{
	int currentYPosition = 0;
	float currentXPosition = 0;

	int levelLength = level.GetLength();
	int currentIndex = 0;

	while (currentIndex < levelLength)
	{
		int currentPlatformLength = 0;

		currentYPosition = level.m_height[currentIndex];
		currentIndex++;
		currentPlatformLength++;
		while (currentIndex < levelLength && level.m_height[currentIndex] == JUMP_LEVEL_ID)
		{
			currentIndex++;
			currentXPosition++;
		}
		while (currentIndex < levelLength && level.m_height[currentIndex] == currentYPosition)
		{
			currentIndex++;
			currentPlatformLength++;
		}
		currentXPosition += currentPlatformLength;

		Platform platform(glm::vec4(currentXPosition - currentPlatformLength / 2.0f, currentYPosition, 0, 1), glm::vec4(currentPlatformLength, 1, 1, 1));
		currentPlatformLength = 0;
	}
}

} // namespace SceneManager
} // namespace Atum
