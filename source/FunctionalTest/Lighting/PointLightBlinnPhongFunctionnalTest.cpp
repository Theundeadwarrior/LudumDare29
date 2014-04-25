#include "FunctionalTest/Lighting/PointLightBlinnPhongFunctionnalTest.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"

namespace Atum
{
namespace FunctionnalTest
{

//---------------------------------------
int TestPointLightBlinnPhongPlainColor(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
int TestPointLightBlinnPhongDiffuseMap(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene, SceneManager::MaterialParameters& materialParameters, SceneManager::ShaderListID shaderlistId);
int TestPointLightBlinnPhongAmbient(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
int TestPointLightBlinnPhongDiffuse(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
int TestPointLightBlinnPhongSpecular(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
int TestPointLightBlinnPhongMultiLights(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);

//---------------------------------------
int PointLightBlinnPhongTest(GraphicsEngine::GraphicsEngine& graphicsEngine)
{
	//SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	//SceneManager::Scene scene;

	/////////SCENE INITIALIZATION

	////material
	//std::string vsPath("../../data/shaders/Generic_Vertex_Shader.cg");
	//std::string blinnphongfsPath("../../data/shaders/Blinn-Phong_Fragment_Shader.cg");

	//SceneManager::ShaderListID shaderListId = 
	//	sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), blinnphongfsPath.c_str() );

	//SceneManager::MaterialParameters materialParameters;

	//SceneManager::MaterialID materialIDPlainColor = 
	//	sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, shaderListId);

	////geometry
	//SceneManager::GeometryManager* const gm = sceneManager.GetGeometryManager();

	//SceneManager::Transform transf = SceneManager::Transform(glm::vec3(0.2,0.4,-0.35), glm::quat(0.1,-0.1,-0.02, 0.99), glm::vec3(1,1,1));
	//SceneManager::Object object(materialIDPlainColor, gm->GetStandardPlaneGeometryId(), transf);

	//scene.AddObject(&object);

	////point light
	//SceneManager::LightBaseParams lightBaseParams;
	//lightBaseParams.ambient = glm::vec4(0.15,0.1,0.05,1);
	//lightBaseParams.diffuse = glm::vec4(1,0.6,0.3,1);
	//lightBaseParams.specular = glm::vec4(1,0.6,0.3,1);
	//SceneManager::PointLight pointLight = SceneManager::PointLight(lightBaseParams, SceneManager::Transform(), 5.0f);
	//scene.AddPointLight(&pointLight);

	//// camera
	//SceneManager::PerspectiveCameraParams params(45, 800.0f/600.0f, 0.1f, 1000.0f);
	//SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(-0.36,0.48,1.73), glm::vec3(1,0,-10), glm::vec3(0,1,0));

	//scene.AddCamera(camera);

	////update camera matrices
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	//glm::mat4x4* test = (static_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);
	////////END INITIALIZATION

	//sceneManager.AddScene(&scene);
	//sceneManager.SetCurrentScene(0);

	////toremove once we have macros disabling ui in graphics engine
	//UserInterface::UiManager::GetInstance().EnableCompleteUi();

	//int errorCount = 0;

	//errorCount += TestPointLightBlinnPhongPlainColor(graphicsEngine, scene);
	//errorCount += TestPointLightBlinnPhongDiffuseMap(graphicsEngine, scene, materialParameters, shaderListId);
	//errorCount += TestPointLightBlinnPhongAmbient(graphicsEngine, scene);
	//errorCount += TestPointLightBlinnPhongDiffuse(graphicsEngine, scene);
	//errorCount += TestPointLightBlinnPhongSpecular(graphicsEngine, scene);
	//errorCount += TestPointLightBlinnPhongMultiLights(graphicsEngine, scene);

	////toremove once we have macros disabling ui in graphics engine
	//UserInterface::UiManager::GetInstance().DisableCompleteUi();

	//sceneManager.ClearAllResources();

	//return errorCount;
	return 0;
}

//---------------------------------------
int TestPointLightBlinnPhongPlainColor(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongPlainColor.bmp");
}

//---------------------------------------
int TestPointLightBlinnPhongDiffuseMap(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene, SceneManager::MaterialParameters& materialParameters, SceneManager::ShaderListID shaderlistId)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();

	std::string diffusemapPath("../../FunctionnalTest/data/textures/DiffuseMap.bmp");
	Utilities::Image::ImageParameters<unsigned char> imageParameters;
	Utilities::Image::LoadImageFromFile<unsigned char>(imageParameters,diffusemapPath.c_str());
	unsigned int diffusemapID = 
		sceneManager.GetTextureManager()->CreateTexture(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	materialParameters.diffuseMapParam = SceneManager::TextureParameter(diffusemapID);

	SceneManager::MaterialID materialIDTextured = 
		sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, shaderlistId);

	(*scene.GetBeginObjectList())->SetMaterialID(materialIDTextured);

	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongDiffuseMap.bmp");
}

//---------------------------------------
int TestPointLightBlinnPhongAmbient(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0.5,0.4,0.3,1));
	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0,0,0,0));
	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0,0,0,0));

	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongAmbient.bmp");
}
//---------------------------------------
int TestPointLightBlinnPhongDiffuse(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0.5,0.4,0.3,1));
	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0,0,0,0));
	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0,0,0,0));

	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongDiffuse.bmp");
}
//---------------------------------------
int TestPointLightBlinnPhongSpecular(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0.5,0.4,0.3,1));
	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0,0,0,0));
	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0,0,0,0));

	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongSpecular.bmp");
}
//---------------------------------------
int TestPointLightBlinnPhongMultiLights(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
{
	SceneManager::LightBaseParams light2BaseParams;
	light2BaseParams.ambient = glm::vec4(0.05,0.01,0.07,1);
	light2BaseParams.diffuse = glm::vec4(0.4,0.5,0.0,1);
	light2BaseParams.specular = glm::vec4(0.1,0.1,0.2,1);
	SceneManager::PointLight pointLight2 = SceneManager::PointLight(light2BaseParams, SceneManager::Transform(), 3.0f);
	scene.AddPointLight(&pointLight2);

	SceneManager::LightBaseParams light3BaseParams;
	light3BaseParams.ambient = glm::vec4(0.015,0.03,0.025,1);
	light3BaseParams.diffuse = glm::vec4(0.6,1,0.3,1);
	light3BaseParams.specular = glm::vec4(1,0.3,0.6,1);
	SceneManager::PointLight pointLight3 = SceneManager::PointLight(light3BaseParams, SceneManager::Transform(), 1.0f);
	scene.AddPointLight(&pointLight3);

	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightBlinnPhongMultiLights.bmp");
}

}
}
