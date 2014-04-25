#include <iostream>
#include <gtest/gtest.h>
#include <string>

// SceneManager
#include "UnitTest/SceneManager/CameraTest.h"
#include "UnitTest/SceneManager/MaterialTest.h"
#include "UnitTest/SceneManager/PointLightTest.h"
#include "UnitTest/SceneManager/TransformTest.h"

// Utilities
#include "UnitTest/Utilities/IndexerTest.h"
#include "UnitTest/Utilities/BrainLoaderTest.h"
#include "UnitTest/Utilities/ObjectLoaderTest.h"

// Physics engine unit tests
#include "UnitTest/PhysicsEngine/PhysicsEngineTest.h"

// Requirements
#include "GraphicsEngine/GraphicsEngine.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"

#define GLM_PRECISION_HIGHP_FLOAT

using namespace std;

int main(int argc, char *argv[])
{
	Atum::LowLevelGraphics::WindowManager& windowManager = Atum::LowLevelGraphics::WindowManager::GetInstance();
	Atum::GraphicsEngine::GraphicsEngine* graphicsEngine = new Atum::GraphicsEngine::GraphicsEngine(argc,argv);

	testing::InitGoogleTest(&argc, argv);
	int success = RUN_ALL_TESTS();
	system("pause");
	return success;
}
