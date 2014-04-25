#ifndef FUNCTIONNALTEST_INCLUDEPACKAGE_H
#define FUNCTIONNALTEST_INCLUDEPACKAGE_H

#include "GraphicsEngine/GraphicsEngine.h"
#include "SceneManager/SceneManager.h"
#include "UserInterface/Ui/UiManager.h" //toremove

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Material/Material.h"
#include "SceneManager/Objects/Object.h"
#include "LowLevelGraphics/Geometry/Geometry.h"
#include "SceneManager/Camera/PerspectiveCamera.h"
#include "SceneManager/Utilities/Transform.h"
#include "Utilities/Image/ImageUtilities.h"
#include "CImg/CImg.h"

#define GLM_PRECISION_HIGHP_FLOAT
#define FUNCTIONNAL_TEST_SUCCESS 0
#define FUNCTIONNAL_TEST_FAILURE 1
#define FRAMES_BEFORE_SCREENSHOT 10

namespace Atum
{
namespace FunctionnalTest
{
inline cimg_library::CImg<unsigned char> RenderSceneToImage(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	for(unsigned int i = 0; i < FRAMES_BEFORE_SCREENSHOT; ++i)
	{
		graphicsEngine.StartRendering(&scene);
		graphicsEngine.StopRendering();
	}

	graphicsEngine.GetPhotographer().RequestScreenShot();

	graphicsEngine.StartRendering(&scene);
	graphicsEngine.StopRendering();

	unsigned char* screenshotData = graphicsEngine.GetPhotographer().GetLastScreenShot();

	unsigned int size = DEFAULT_WINDOW_WIDTH*DEFAULT_WINDOW_HEIGHT*3;
	unsigned char* orderedScreenshotData = new unsigned char[size];
	for(int i = 0; i < size; i++)
	{
		orderedScreenshotData[i] = screenshotData[(i*3)%(size-1)];
	}

	cimg_library::CImg<unsigned char> img(orderedScreenshotData, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 1, 3);
	img.mirror('y');
	delete orderedScreenshotData;

	return img;
}

inline int RenderAndCompare(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene, const char* imagePath)
{
	for(unsigned int i = 0; i < FRAMES_BEFORE_SCREENSHOT; ++i)
	{
		graphicsEngine.StartRendering(&scene);
		graphicsEngine.StopRendering();
	}

	graphicsEngine.GetPhotographer().RequestScreenShot();

	graphicsEngine.StartRendering(&scene);
	graphicsEngine.StopRendering();

	unsigned char* screenshotData = graphicsEngine.GetPhotographer().GetLastScreenShot();

	Utilities::Image::ImageParameters<unsigned char> screenshotParams;
	screenshotParams.height = DEFAULT_WINDOW_HEIGHT;
	screenshotParams.width = DEFAULT_WINDOW_WIDTH;
	screenshotParams.spectrum = 3;

	unsigned int size = screenshotParams.width*screenshotParams.height*screenshotParams.spectrum;
	screenshotParams.imageData.reserve(size);

	for(unsigned int i = 0; i < size; ++i)
	{
		screenshotParams.imageData.push_back(screenshotData[i]);
	}

	//todo : save only if file doesn't exist, add comparison if it exists, if the comparison fails, log the error and save the new image for reference
	Utilities::Image::SaveImageToFile<unsigned char>(screenshotParams, imagePath);
	return FUNCTIONNAL_TEST_SUCCESS;
}
}
}

#endif