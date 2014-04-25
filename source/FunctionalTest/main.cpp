#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "GraphicsEngine/GraphicsEngine.h"
#include "SceneManager/Scene/Scene.h"

#include "FunctionalTest/FunctionnalTestIncludePackage.h"
#include "FunctionalTest/Lighting/PointLightPhongFunctionnalTest.h"
#include "FunctionalTest/FunctionalTestData.h"
#include "FunctionalTest/Material/MaterialFunctionnalTest.h"
#include "FunctionalTest/PointCloud/PointCloudFunctionnalTest.h"
#include "FunctionalTest/Geometry/GeometryFunctionnalTest.h"
#include "Utilities/Win32/Win32Utilities.h"
#include "Utilities/Win32/FileSyst.h"

#include "CImg/CImg.h"

using namespace Atum;

std::string IntToString(int i);
std::string GetImageDataBasePath(char* path);

int main(int argc, char *argv[])
{
	FunctionnalTest::FunctionalTestData::SetFunctionalTestPath(GetImageDataBasePath(argv[0]));
	GraphicsEngine::GraphicsEngine graphicsEngine(argc,argv);
	SceneManager::Scene scene;

	std::vector<FunctionnalTest::FunctionalTestData> tests;
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_GEOMETRY, "GeometryLoaderTest", 1, FunctionnalTest::GeometryLoaderTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_LIGHTING, "PointLightPhongTest", 1, FunctionnalTest::PointLightPhongTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_MATERIAL, "MaterialTextureTest", 1, FunctionnalTest::MaterialTextureTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_MATERIAL, "MaterialParallaxMapTest", 1, FunctionnalTest::MaterialParallaxMapTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_MATERIAL, "MaterialSkyBoxUpperRightTest", 1, FunctionnalTest::MaterialSkyboxUpperRightTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_MATERIAL, "MaterialSkyBoxLowerLeftTest", 1, FunctionnalTest::MaterialSkyboxLowerLeftTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_MATERIAL, "MaterialVariationTest", 1, FunctionnalTest::MaterialVariationTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_POINTCLOUD, "PointCloudTest", 1, FunctionnalTest::PointCloudTest));
	tests.push_back(FunctionnalTest::FunctionalTestData(FunctionnalTest::TEST_TYPE_POINTCLOUD, "PointCloudSliceTest", 1, FunctionnalTest::PointCloudSliceTest));

	int errorCount = 0;
	int differenceCount = 0;
	int newFileCount = 0;

	for(int i = 0; i < tests.size(); i++)
	{
		scene = SceneManager::Scene();
		tests[i].ExecuteFunctionalTest(graphicsEngine, scene);
		char fullPath[_MAX_PATH];
		if(_fullpath(fullPath, tests[i].GetFunctionalTestPath().c_str(), _MAX_PATH ) != NULL)
			Win32Utilities::CreateFolder(fullPath);

		Win32Utilities::FileSyst fs(tests[i].GetFunctionalTestPath());
		std::vector<std::string> files = fs.GetAllFiles(false);

		// #if ref is not set up 
		std::vector<std::string>::iterator it = std::find(files.begin(),files.end(), "ref");
		if(it == files.end())
		{
			cimg_library::CImgDisplay disp1(*tests[i].GetScreenShot(), "New Reference?");
			char answer;
			std::cout << std::endl << "Reference not found for " << tests[i].GetTestName() << ". Would you like to set the displayed image as the new reference?" << std::endl;
			std::cin >> answer;

			if(answer == 'y' || answer == 'Y')
			{
				// save new ref
				std::string fullFileName = tests[i].GetFunctionalTestPath() + "ref.bmp";
				tests[i].GetScreenShot()->save_bmp(fullFileName.c_str());
				newFileCount++;
			}
			disp1.close();
		}

		// if we found a ref inside the folder
		else
		{
			std::string fullFileName = tests[i].GetFunctionalTestPath() + "ref.bmp";
			cimg_library::CImg<unsigned char> diff;
			cimg_library::CImg<unsigned char> currentRef(fullFileName.c_str());
			float diffPercentage = Utilities::Image::CalculateImageDifference(*tests[i].GetScreenShot(), currentRef, diff);

			// Image is too different from what we expected, we need to check if there is a new ref or not.
			if(diffPercentage > tests[i].GetThreshold())
			{
				cimg_library::CImgDisplay disp1(*tests[i].GetScreenShot(), "Current Rendering");
				cimg_library::CImgDisplay disp2(currentRef, "Reference");
				cimg_library::CImgDisplay disp3(diff, "Difference");

				char answer;
				std::cout << std::endl << "The current render differs from the current reference for " << tests[i].GetTestName() << ". Would you like to update the reference?" << std::endl;
				std::cin >> answer;

				// the new image is not a ref, so we add it as with a number.
				if(answer == 'n' || answer == 'N')
				{
					// save new image and the diff
					std::string newImageName = tests[i].GetFunctionalTestPath() + IntToString((files.size() - 1) / 2) + ".bmp";
					std::string newDiff = tests[i].GetFunctionalTestPath() + "d" + IntToString((files.size() - 1) / 2) + ".bmp";

					tests[i].GetScreenShot()->save_bmp(newImageName.c_str());
					diff.save_bmp(newDiff.c_str());

					std::cout << std::endl << "Test results in an error for " << tests[i].GetTestName() << std::endl;
					errorCount++;
				}

				// Saves the image as the new ref and back-up the one before
				else if(answer == 'y' || answer == 'Y')
				{
					std::string oldRef = tests[i].GetFunctionalTestPath() + "oldref.bmp";
					currentRef.save_bmp(oldRef.c_str());

					std::string newRef = tests[i].GetFunctionalTestPath() + "ref.bmp";
					tests[i].GetScreenShot()->save_bmp(newRef.c_str());
				}
				disp1.close();
				disp2.close();
				disp3.close();

				differenceCount++;
			}
		}
	}

	std::cout << std::endl << "There are " << newFileCount << " new tests." << std::endl << std::endl;
	std::cout << "There are "<< differenceCount << " tests resulting in a difference from the original." << std::endl;
	std::cout << errorCount << " errors were found." << std::endl;

	if(!errorCount)
	{
		std::cout << "FUNCTIONNAL TESTS : PASS" << std::endl << std::endl;
	}
	else
	{
		std::cout << "FUNCTIONNAL TESTS : FAIL" << std::endl << std::endl;
	}

	system("pause");

	return 0;
}

std::string IntToString(int i)
{
	std::stringstream ss;//create a stringstream
	ss << i;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::string GetImageDataBasePath( char* path )
{
	std::string sPath(path);

	for(int i = 0; i < 5; i++)
	{
		size_t found = sPath.find_last_of("\\");
		sPath = sPath.substr(0,found);
	}

	//std::replace(sPath.begin(), sPath.end(), '\\', '/');

	return sPath + "\\";
}

