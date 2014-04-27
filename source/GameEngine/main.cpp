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
#define MILLISECOND_FRAME_TIME 16.66666666666667

using namespace Atum;

int main(int argc, char *argv[])
{
	LowLevelGraphics::WindowManager& windowManager = LowLevelGraphics::WindowManager::GetInstance();
	GraphicsEngine::GraphicsEngine* graphicsEngine = new GraphicsEngine::GraphicsEngine(argc,argv);
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::ShaderListManager* shaderListManager = sceneManager.GetShaderListManager();
	SceneManager::GeometryManager* const gm = sceneManager.GetGeometryManager();

	TestSceneLoader sceneTestLoader(sceneManager);

	std::vector<SceneManager::Scene*> scenes = sceneManager.GetSceneList();

	unsigned long long int lastTicks = GetTickCount64();
	unsigned long long int elapsedTicks;

	while(windowManager.GetCurrentWindowId() != 0)
	{

		Utilities::Timer::GetInstance()->MarkLap();
		Utilities::Timer::GetInstance()->ResetTimer();

		sceneManager.UpdateCurrentScene();

		graphicsEngine->StartRendering(sceneManager.GetCurrentScene());
		graphicsEngine->StopRendering();

		double testtime = Utilities::Timer::GetInstance()->GetLapTime();

		// todo : use something else to avoid draining the processor
		Sleep(MILLISECOND_FRAME_TIME - testtime);
		/////////////////////////////////////////////////////////////
	}
	delete graphicsEngine;
	return 0;
}
