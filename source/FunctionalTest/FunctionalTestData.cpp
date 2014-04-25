#include "FunctionalTestData.h"
#include "SceneManager/Scene/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"

#include "Utilities/Win32/Win32Utilities.h"


namespace Atum
{
namespace FunctionnalTest
{

std::string FunctionalTestData::m_functionalTestPath;

FunctionalTestData::FunctionalTestData( FuncType testType, const std::string& testName, unsigned int threshold, void (*testingFunction)(SceneManager::Scene&) )
	:m_testType(testType),
	m_testName(testName),
	m_threshold(threshold)
{
	m_testingFunction = testingFunction;
}

FunctionalTestData::~FunctionalTestData()
{}

void FunctionalTestData::ExecuteFunctionalTest(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene )
{
	m_testingFunction(scene);
	m_capturedScreen = RenderSceneToImage(graphicsEngine, scene);
}

std::string FunctionalTestData::GetFunctionalTestPath() const
{
        return "..\\..\\FunctionalTest\\" + GetTestTypeName(*this) + "\\" + GetTestName() + "\\";
}

std::string GetTestTypeName( const FunctionalTestData& testData )
{
	if ( testData.GetTestType() == TEST_TYPE_LIGHTING )
		return "Lighting";
	else if ( testData.GetTestType() == TEST_TYPE_TRANSFORM )
		return "Transform";
	else if ( testData.GetTestType() == TEST_TYPE_MATERIAL)
		return "Material";
	else if ( testData.GetTestType() == TEST_TYPE_POINTCLOUD)
		return "PointCloud";
	else if ( testData.GetTestType() == TEST_TYPE_GEOMETRY)
		return "Geometry";
	else
		return "Miscellaneous";
}

}
}
