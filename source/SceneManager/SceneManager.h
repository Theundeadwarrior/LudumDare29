#ifndef SCENEMANAGER_SCENEMANAGER_H
#define SCENEMANAGER_SCENEMANAGER_H

#include <vector>

#include "SceneManager/Manager/MaterialManager.h"
#include "SceneManager/Manager/ShaderListManager.h"
#include "SceneManager/Manager/GeometryManager.h"
#include "SceneManager/Manager/TextureManager.h"

namespace Atum
{
namespace SceneManager
{
	class Scene;

	class SceneManager
	{
	public:
		static SceneManager& GetInstance();
		~SceneManager();
		
		void AddScene(Scene* scene){m_sceneList.push_back(scene);}
		void RemoveScene(int id);
		void SetCurrentScene(int id) {m_currentScene = m_sceneList[id];}
		Scene* GetCurrentScene();
		std::vector<Scene*> GetSceneList() { return m_sceneList; };

		void UpdateCurrentScene();

		void ClearAllResources();
		void ClearAllScenes();

		MaterialManager* const GetMaterialManager();
		ShaderListManager* const GetShaderListManager();
		GeometryManager* const GetGeometryManager();
        TextureManager* const GetTextureManager();

	private:
		SceneManager();
		SceneManager(SceneManager const&); //don't implement
		void operator=(SceneManager const&); //don't implement
		std::vector<Scene*> m_sceneList;
		ShaderListManager m_shaderListManager;
		MaterialManager m_materialManager;
		GeometryManager m_geometryManager;
        TextureManager m_textureManager;
		Scene* m_currentScene;
	
	};

} // namespace SceneManager
} // namespace Atum


#endif
