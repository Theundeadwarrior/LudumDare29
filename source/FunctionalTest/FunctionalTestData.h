#ifndef FUNCTIONNALTEST_DATA_H
#define FUNCTIONNALTEST_DATA_H

#include <string>
#include "CImg\CImg.h"

namespace Atum
{
namespace SceneManager{ class Scene; }
namespace GraphicsEngine{ class GraphicsEngine; }

namespace FunctionnalTest
{

//keep synced with GetTestTypeName!
enum FuncType {
	TEST_TYPE_MISCELLANEOUS = 0,
	TEST_TYPE_GEOMETRY,
	TEST_TYPE_LIGHTING,
	TEST_TYPE_TRANSFORM,
	TEST_TYPE_MATERIAL,
	TEST_TYPE_POINTCLOUD,
	FUNC_TYPE_COUNT //DONT' TOUCH, OR I'LL CHOP YOUR HANDS OFF
};

class FunctionalTestData
{
	public:
		static void SetFunctionalTestPath(std::string path){m_functionalTestPath = path;}

	public:
		FunctionalTestData(
			FuncType testType, const std::string& testName, unsigned int threshold, void (*testingFunction)(SceneManager::Scene&));
		~FunctionalTestData();

		FuncType	GetTestType() const { return m_testType; }
		std::string	GetTestName() const { return m_testName; }
		float GetThreshold() const { return m_threshold; }
		cimg_library::CImg<unsigned char>* const GetScreenShot(){return &m_capturedScreen;}

		void		SetTestType(FuncType val) { m_testType = val; }
		void		SetTestName(std::string val) { m_testName = val; }
		void		SetThreshold(float val) { m_threshold = val; }

		void ExecuteFunctionalTest(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
		std::string GetFunctionalTestPath() const;

	private:
		static std::string m_functionalTestPath;

	private:
		FuncType m_testType;
		std::string m_testName;
		float m_threshold;
		cimg_library::CImg<unsigned char> m_capturedScreen;
		void (*m_testingFunction)(SceneManager::Scene&);
};

std::string GetTestTypeName(const FunctionalTestData& testData);

}
}

#endif
