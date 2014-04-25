#include <stdio.h>
#include <windows.h>

#include "GraphicsEngine/GraphicsEngine.h"
#include "UserInterface/Ui/UiManager.h"
#include "SceneManager/SceneManager.h"
#include "PhysicsEngine/PhysicsEngine.h"

#include "LowLevelGraphics/WindowManager/WindowManager.h"
#include "TestSceneLoader.h"
#include "Utilities/Timer/Timer.h"

#define GLM_PRECISION_HIGHP_FLOAT

using namespace Atum;

int main(int argc, char *argv[])
{
	LowLevelGraphics::WindowManager& windowManager = LowLevelGraphics::WindowManager::GetInstance();
	GraphicsEngine::GraphicsEngine* graphicsEngine = new GraphicsEngine::GraphicsEngine(argc,argv);
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::ShaderListManager* shaderListManager = sceneManager.GetShaderListManager();
	SceneManager::GeometryManager* const gm = sceneManager.GetGeometryManager();

	TestSceneLoader sceneTestLoader(sceneManager);

	PhysicsEngine::PhysicsEngine& physicsEngine = PhysicsEngine::PhysicsEngine::GetInstance();
	
	std::vector<SceneManager::Scene*> scenes = sceneManager.GetSceneList();
	if (scenes.size() > 3)
	{
		physicsEngine.SetScene(scenes[3]);
	}

	//ray-picking
	UserInterface::UiManager::GetInstance().EnableCompleteUi();

	unsigned long long int lastTicks = GetTickCount64();
	unsigned long long int elapsedTicks;

	while(windowManager.GetCurrentWindowId() != 0)
	{
		Utilities::Timer::GetInstance()->MarkLap();
		Utilities::Timer::GetInstance()->ResetTimer();

		physicsEngine.Advance(Utilities::Timer::GetInstance()->GetLapTime());
		physicsEngine.UpdateGraphicScene();

		graphicsEngine->StartRendering(sceneManager.GetCurrentScene());
		graphicsEngine->StopRendering();

		// todo : use something else to avoid draining the processor
		Sleep(1);
		/////////////////////////////////////////////////////////////
	}
	delete graphicsEngine;
	return 0;
}
