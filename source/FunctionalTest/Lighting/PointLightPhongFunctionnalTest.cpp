#include "FunctionalTest/Lighting/PointLightPhongFunctionnalTest.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"


namespace Atum
{
namespace FunctionnalTest
{

//---------------------------------------
//int TestPointLightPhongPlainColor(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
//int TestPointLightPhongDiffuseMap(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene, SceneManager::MaterialParameters& materialParameters,  SceneManager::ShaderListID shaderListId);
//int TestPointLightPhongAmbient(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
//int TestPointLightPhongDiffuse(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
//int TestPointLightPhongSpecular(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);
//int TestPointLightPhongMultiLights(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene);

//---------------------------------------
void PointLightPhongTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	// Paths to data
	std::string vsPath("../../data/shaders/GLSL_Generic_Vertex_Shader.vx");
	std::string fsPath("../../data/shaders/GLSL_Generic_Fragment_Shader.fg");

	SceneManager::ShaderListID shaderID = sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), fsPath.c_str() , SceneManager::PHONG_SHADING);
	SceneManager::MaterialParameters materialParam;
	materialParam.phongParam = SceneManager::PhongParameter(glm::vec4(1,1,1,1),glm::vec4(0.8,0.8,0.8,1),glm::vec4(0.8,0.8,0.8,1),60);
	SceneManager::MaterialID materialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParam, shaderID);

	SceneManager::Transform transf1 = SceneManager::Transform(glm::vec3(-2,2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object1 = new SceneManager::Object(materialID, gm->GetStandardSphereGeometryId(), transf1);
	SceneManager::Transform transf2 = SceneManager::Transform(glm::vec3(-2,-2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object2 = new SceneManager::Object(materialID, gm->GetStandardSphereGeometryId(), transf2);
	SceneManager::Transform transf3 = SceneManager::Transform(glm::vec3(2,2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object3 = new SceneManager::Object(materialID, gm->GetStandardSphereGeometryId(), transf3);
	SceneManager::Transform transf4 = SceneManager::Transform(glm::vec3(2,-2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object4 = new SceneManager::Object(materialID, gm->GetStandardSphereGeometryId(), transf4);
	scene.AddObject(object1);
	scene.AddObject(object2);
	scene.AddObject(object3);
	scene.AddObject(object4);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//Lights
	SceneManager::LightBaseParams light1BaseParams;
	light1BaseParams.ambient = glm::vec4(0,0.5,0.5,1);
	light1BaseParams.diffuse = glm::vec4(0,0,0,0);
	light1BaseParams.specular = glm::vec4(0,0,0,0);
	SceneManager::LightBaseParams light2BaseParams;
	light2BaseParams.ambient = glm::vec4(0,0,0,0);
	light2BaseParams.diffuse = glm::vec4(1,1,0,1);
	light2BaseParams.specular = glm::vec4(1,1,0,1);
	SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(), 5.0f);
	SceneManager::PointLight* pointLight2 = new SceneManager::PointLight(light2BaseParams, SceneManager::Transform(glm::vec3(0,0,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 50.0f);
	scene.AddPointLight(pointLight1);
	scene.AddPointLight(pointLight2);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

////---------------------------------------
//int TestPointLightPhongPlainColor(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
//{
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongPlainColor.bmp");
//}
//
////---------------------------------------
//int TestPointLightPhongDiffuseMap(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene, SceneManager::MaterialParameters& materialParameters, SceneManager::ShaderListID shaderListId)
//{
//	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
//
//	std::string diffusemapPath("../../FunctionnalTest/data/textures/DiffuseMap.bmp");
//	Utilities::Image::ImageParameters<unsigned char> imageParameters;
//	Utilities::Image::LoadImageFromFile<unsigned char>(imageParameters,diffusemapPath.c_str());
//	unsigned int diffusemapID = 
//		sceneManager.GetTextureManager()->CreateTexture(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);
//
//	materialParameters.textureParam = SceneManager::TextureParameter(diffusemapID);
//
//	SceneManager::MaterialID materialIDTextured = 
//		sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, shaderListId);
//
//	(*scene.GetBeginObjectList())->SetMaterialID(materialIDTextured);
//
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongDiffuseMap.bmp");
//}
//
////---------------------------------------
//int TestPointLightPhongAmbient(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
//{
//	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0.5,0.4,0.3,1));
//	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0,0,0,0));
//	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0,0,0,0));
//
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongAmbient.bmp");
//}
////---------------------------------------
//int TestPointLightPhongDiffuse(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
//{
//	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0.5,0.4,0.3,1));
//	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0,0,0,0));
//	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0,0,0,0));
//
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongDiffuse.bmp");
//}
////---------------------------------------
//int TestPointLightPhongSpecular(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
//{
//	(*scene.GetBeginPointLightList())->SetSpecular(glm::vec4(0.5,0.4,0.3,1));
//	(*scene.GetBeginPointLightList())->SetAmbient(glm::vec4(0,0,0,0));
//	(*scene.GetBeginPointLightList())->SetDiffuse(glm::vec4(0,0,0,0));
//
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongSpecular.bmp");
//}
////---------------------------------------
//int TestPointLightPhongMultiLights(GraphicsEngine::GraphicsEngine& graphicsEngine, SceneManager::Scene& scene)
//{
//	SceneManager::LightBaseParams light2BaseParams;
//	light2BaseParams.ambient = glm::vec4(0.05,0.01,0.07,1);
//	light2BaseParams.diffuse = glm::vec4(0.4,0.5,0.0,1);
//	light2BaseParams.specular = glm::vec4(0.1,0.1,0.2,1);
//	SceneManager::PointLight pointLight2 = SceneManager::PointLight(light2BaseParams, SceneManager::Transform(), 3.0f);
//	scene.AddPointLight(&pointLight2);
//
//	SceneManager::LightBaseParams light3BaseParams;
//	light3BaseParams.ambient = glm::vec4(0.015,0.03,0.025,1);
//	light3BaseParams.diffuse = glm::vec4(0.6,1,0.3,1);
//	light3BaseParams.specular = glm::vec4(1,0.3,0.6,1);
//	SceneManager::PointLight pointLight3 = SceneManager::PointLight(light3BaseParams, SceneManager::Transform(), 1.0f);
//	scene.AddPointLight(&pointLight3);
//
//	return RenderAndCompare(graphicsEngine, scene, "../../FunctionnalTest/ScreenShot/PointLight/PointLightPhongMultiLights.bmp");
//}

}
}
