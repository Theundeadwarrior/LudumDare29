#include "FunctionalTest/Material/MaterialFunctionnalTest.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"

namespace Atum
{
namespace FunctionnalTest
{

//-----------------------------------------------------------------------------
void MaterialTextureTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	// Paths to data
	std::string vsPath("../../data/shaders/GLSL_Generic_Vertex_Shader.vx");
	std::string fsPath("../../data/shaders/GLSL_Generic_Fragment_Shader.fg");
	std::string texturePath("../../data/textures/bunny_texture.bmp");
	std::string texturePath2("../../data/textures/ParallaxTex.bmp");

	SceneManager::ShaderListID shaderID = sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), fsPath.c_str() , SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP);
	Utilities::Image::ImageParameters<unsigned char> imageParameters1;
	Utilities::Image::LoadImageFromFile<unsigned char>(imageParameters1,texturePath.c_str());
	SceneManager::TextureId textureID1 = sceneManager.GetTextureManager()->CreateTexture(imageParameters1, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	Utilities::Image::ImageParameters<unsigned char> imageParameters2;
	Utilities::Image::LoadImageFromFile<unsigned char>(imageParameters2,texturePath2.c_str());
	SceneManager::TextureId textureID2 = sceneManager.GetTextureManager()->CreateTexture(imageParameters2, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	SceneManager::MaterialParameters materialParam1;
	materialParam1.diffuseMapParam = SceneManager::TextureParameter(textureID1); // We are adding texture support to the material;
	materialParam1.phongParam = SceneManager::PhongParameter(glm::vec4(1,1,1,1), glm::vec4(1,1,1,1),glm::vec4(1,1,1,1),10);
	SceneManager::MaterialID materialID1 = sceneManager.GetMaterialManager()->CreateMaterial(materialParam1, shaderID);

	SceneManager::MaterialParameters materialParam2;
	materialParam2.diffuseMapParam = SceneManager::TextureParameter(textureID2); // We are adding texture support to the material;
	materialParam2.phongParam = SceneManager::PhongParameter(glm::vec4(1,1,1,1), glm::vec4(1,1,1,1),glm::vec4(1,1,1,1),10);
	SceneManager::MaterialID materialID2 = sceneManager.GetMaterialManager()->CreateMaterial(materialParam2, shaderID);

	SceneManager::Transform transf1 = SceneManager::Transform(glm::vec3(-2,-2,0), glm::quat(0,-1,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object1 = new SceneManager::Object(materialID1, gm->GetStandardCubeGeometryId(), transf1);
	SceneManager::Transform transf2 = SceneManager::Transform(glm::vec3(2,2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object2 = new SceneManager::Object(materialID2, gm->GetStandardSphereGeometryId(), transf2);
	SceneManager::Transform transf3 = SceneManager::Transform(glm::vec3(2,-2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object3 = new SceneManager::Object(materialID1, gm->GetStandardSphereGeometryId(), transf3);
	scene.AddObject(object1);
	scene.AddObject(object2);
	scene.AddObject(object3);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//Lights
	SceneManager::LightBaseParams light1BaseParams;
	light1BaseParams.ambient = glm::vec4(1,1,1,1);
	SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(), 5.0f);
	scene.AddPointLight(pointLight1);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

//-----------------------------------------------------------------------------
void MaterialParallaxMapTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	// Paths to data
	std::string vsPath("../../data/shaders/GLSL_Generic_Vertex_Shader.vx");
	std::string fsPath("../../data/shaders/GLSL_Generic_Fragment_Shader.fg");
	std::string texturePath("../../data/textures/ParallaxTex.bmp");
	std::string parallaxPath("../../data/textures/ParallaxMap.png");

	// Init parallax map shader
	SceneManager::ShaderListID parallaxMapTexShaderID = sceneManager.GetShaderListManager()->CreateShaderList(vsPath.c_str(), fsPath.c_str(), SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP | SceneManager::PARALLAX_MAP);
	SceneManager::ShaderListID parallaxMapShaderID = sceneManager.GetShaderListManager()->CreateShaderList(vsPath.c_str(), fsPath.c_str(), SceneManager::PHONG_SHADING | SceneManager::PARALLAX_MAP);

	Utilities::Image::ImageParameters<unsigned char> parallaxMapNormal;
	Utilities::Image::LoadImageFromFile(parallaxMapNormal, parallaxPath.c_str());
	SceneManager::TextureId parallaxMapNormalID = sceneManager.GetTextureManager()->CreateTexture(parallaxMapNormal, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

	Utilities::Image::ImageParameters<unsigned char> parallaxMapTexture;
	Utilities::Image::LoadImageFromFile(parallaxMapTexture, texturePath.c_str());
	SceneManager::TextureId parallaxMapTextureID = sceneManager.GetTextureManager()->CreateTexture(parallaxMapTexture, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//Paralax Map material
	SceneManager::MaterialParameters paralaxTexMaterialParam;
	paralaxTexMaterialParam.diffuseMapParam = SceneManager::TextureParameter(parallaxMapTextureID);
	paralaxTexMaterialParam.parallaxParam = SceneManager::ParallaxMapParameters(parallaxMapNormalID,0.045,0.1);
	paralaxTexMaterialParam.phongParam = SceneManager::PhongParameter(glm::vec4(0.05,0.05,0.05,1), glm::vec4(0.9,0.9,0.9,1), glm::vec4(0.1,0.1,0.05,1), 20);
	SceneManager::MaterialID parallaxTexMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(paralaxTexMaterialParam, parallaxMapTexShaderID);
	
	//Normal Map material
	SceneManager::MaterialParameters normalTexMaterialParam;
	normalTexMaterialParam.diffuseMapParam = SceneManager::TextureParameter(parallaxMapTextureID);
	normalTexMaterialParam.parallaxParam = SceneManager::ParallaxMapParameters(parallaxMapNormalID,0.0,0.0);
	normalTexMaterialParam.phongParam = SceneManager::PhongParameter(glm::vec4(0.05,0.05,0.05,1), glm::vec4(0.9,0.9,0.9,1), glm::vec4(0.1,0.1,0.05,1), 20);
	SceneManager::MaterialID normalTexMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(normalTexMaterialParam, parallaxMapTexShaderID);

	//Paralax Map material without diffuse map
	SceneManager::MaterialParameters paralaxMaterialParam;
	paralaxMaterialParam.parallaxParam = SceneManager::ParallaxMapParameters(parallaxMapNormalID,0.045,0.1);
	paralaxMaterialParam.phongParam = SceneManager::PhongParameter(glm::vec4(0.05,0.05,0.05,1), glm::vec4(0.9,0.9,0.9,1), glm::vec4(0.1,0.1,0.05,1), 20);
	SceneManager::MaterialID parallaxMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(paralaxMaterialParam, parallaxMapShaderID);

	SceneManager::Transform transf1 = SceneManager::Transform(glm::vec3(2,2,0), glm::quat(1,0,0,0), glm::vec3(4,4,4));
	SceneManager::Object* object1 = new SceneManager::Object(parallaxTexMaterialID, gm->GetStandardPlaneGeometryId(), transf1);
	SceneManager::Transform transf2 = SceneManager::Transform(glm::vec3(2,-2,0), glm::quat(1,0,0,0), glm::vec3(4,4,4));
	SceneManager::Object* object2 = new SceneManager::Object(normalTexMaterialID, gm->GetStandardPlaneGeometryId(), transf2);
	SceneManager::Transform transf3 = SceneManager::Transform(glm::vec3(-2,0,0), glm::quat(1,0,0,0), glm::vec3(4,4,4));
	SceneManager::Object* object3 = new SceneManager::Object(parallaxMaterialID, gm->GetStandardPlaneGeometryId(), transf3);
	scene.AddObject(object1);
	scene.AddObject(object2);
	scene.AddObject(object3);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//Lights
	SceneManager::LightBaseParams light1BaseParams;
	light1BaseParams.ambient = glm::vec4(1,1,1,1);
	light1BaseParams.diffuse = glm::vec4(1,1,1,1);
	light1BaseParams.specular = glm::vec4(1,1,1,1);
	SceneManager::Transform transf4 = SceneManager::Transform(glm::vec3(0,0,-2), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, transf4, 10.0f);
	scene.AddPointLight(pointLight1);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

//-----------------------------------------------------------------------------
void MaterialSkyboxUpperRightTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	// Init cube map shader
	SceneManager::ShaderListID cubeMapShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_CubeMap_Vertex_Shader.vx", "../../data/shaders/GLSL_CubeMap_Fragment_Shader.fg", NULL);
	// Init cube map texture
	std::vector<Utilities::Image::ImageParameters<unsigned char>> imageParameters;
	imageParameters.resize(6);
	Utilities::Image::LoadImageFromFile(imageParameters[0], "../../data/textures/FunctionnalTestTextures/SkyboxLeft.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[1], "../../data/textures/FunctionnalTestTextures/SkyboxRight.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[2], "../../data/textures/FunctionnalTestTextures/SkyboxBottom.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[3], "../../data/textures/FunctionnalTestTextures/SkyboxTop.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[4], "../../data/textures/FunctionnalTestTextures/SkyboxFront.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[5], "../../data/textures/FunctionnalTestTextures/SkyboxBack.bmp");
	SceneManager::TextureId skyBoxTextureID = sceneManager.GetTextureManager()->CreateTextureSkyBox(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	// Init the skybox material
	SceneManager::MaterialParameters materialParameters;
	materialParameters.skyBoxParam = SceneManager::TextureParameter(skyBoxTextureID);
	SceneManager::MaterialID skyBoxMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, cubeMapShaderID);

	// Init skybox geometry
	LowLevelGraphics::GeometryParameters geometryParameters;
	geometryParameters = Utilities::CreateSkyBoxGeometry(3000.0f);
	SceneManager::GeometryID skyBoxGeometryID = gm->CreateGeometry(geometryParameters);

	// Add scene
	scene.AddSkyBox(new SceneManager::SkyBox(skyBoxMaterialID, skyBoxGeometryID));
	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(0,0,0), glm::vec3(1,1,1), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	// toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

//-----------------------------------------------------------------------------
void MaterialSkyboxLowerLeftTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	// Init cube map shader
	SceneManager::ShaderListID cubeMapShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_CubeMap_Vertex_Shader.vx", "../../data/shaders/GLSL_CubeMap_Fragment_Shader.fg", NULL);
	// Init cube map texture
	std::vector<Utilities::Image::ImageParameters<unsigned char>> imageParameters;
	imageParameters.resize(6);
	Utilities::Image::LoadImageFromFile(imageParameters[0], "../../data/textures/FunctionnalTestTextures/SkyboxLeft.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[1], "../../data/textures/FunctionnalTestTextures/SkyboxRight.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[2], "../../data/textures/FunctionnalTestTextures/SkyboxBottom.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[3], "../../data/textures/FunctionnalTestTextures/SkyboxTop.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[4], "../../data/textures/FunctionnalTestTextures/SkyboxFront.bmp");
	Utilities::Image::LoadImageFromFile(imageParameters[5], "../../data/textures/FunctionnalTestTextures/SkyboxBack.bmp");
	SceneManager::TextureId skyBoxTextureID = sceneManager.GetTextureManager()->CreateTextureSkyBox(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	// Init the skybox material
	SceneManager::MaterialParameters materialParameters;
	materialParameters.skyBoxParam = SceneManager::TextureParameter(skyBoxTextureID);
	SceneManager::MaterialID skyBoxMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, cubeMapShaderID);

	// Init skybox geometry
	LowLevelGraphics::GeometryParameters geometryParameters;
	geometryParameters = Utilities::CreateSkyBoxGeometry(3000.0f);
	SceneManager::GeometryID skyBoxGeometryID = gm->CreateGeometry(geometryParameters);

	// Add scene
	scene.AddSkyBox(new SceneManager::SkyBox(skyBoxMaterialID, skyBoxGeometryID));
	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(0,0,0), glm::vec3(-1,-1,-1), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	// toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

//-----------------------------------------------------------------------------
void MaterialVariationTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* gm = sceneManager.GetGeometryManager();

	//-----------------------------------------------------------------------------
	// SHADERS
	//-----------------------------------------------------------------------------
	std::string vsPath("../../data/shaders/GLSL_Generic_Vertex_Shader.vx");
	std::string fsPath("../../data/shaders/GLSL_Generic_Fragment_Shader.fg");
	std::string texturePath("../../data/textures/bunny_texture.bmp");

	SceneManager::ShaderListID sIdPT = sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), fsPath.c_str(), SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP);
	SceneManager::ShaderListID sIdP = sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), fsPath.c_str(), SceneManager::PHONG_SHADING);
	SceneManager::ShaderListID sId = sceneManager.GetShaderListManager()->CreateShaderList( vsPath.c_str(), fsPath.c_str(), SceneManager::NO_ILLUMINATION); 

	Utilities::Image::ImageParameters<unsigned char> imageParameters;
	Utilities::Image::LoadImageFromFile<unsigned char>(imageParameters,texturePath.c_str());
	SceneManager::TextureId textureID = sceneManager.GetTextureManager()->CreateTexture(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//-----------------------------------------------------------------------------
	// MATERIALS
	//-----------------------------------------------------------------------------
	SceneManager::MaterialParameters materialParam1;
	materialParam1.diffuseMapParam = SceneManager::TextureParameter(textureID); // We are adding texture support to the material;
	materialParam1.phongParam = SceneManager::PhongParameter(glm::vec4(0.3,0.3,0.3,1), glm::vec4(0.5,0.5,0,1), glm::vec4(1,1,1,1), 50);
	SceneManager::MaterialID materialID1 = sceneManager.GetMaterialManager()->CreateMaterial(materialParam1, sIdPT);

	SceneManager::MaterialParameters materialParam2;
	materialParam2.phongParam = SceneManager::PhongParameter(glm::vec4(0,0,0,1), glm::vec4(0.2,0.8,0.8,1), glm::vec4(0,0,0,1), 50);
	SceneManager::MaterialID materialID2 = sceneManager.GetMaterialManager()->CreateMaterial(materialParam2, sIdP);

	SceneManager::MaterialParameters materialParam3;
	materialParam3.plainColorParam = SceneManager::PlainColorParameter(glm::vec4(0.98,0.23,0.51,1));
	SceneManager::MaterialID materialID3 = sceneManager.GetMaterialManager()->CreateMaterial(materialParam3, sId);

	//-----------------------------------------------------------------------------
	// OBJECTS
	//-----------------------------------------------------------------------------
	SceneManager::Transform transf1 = SceneManager::Transform(glm::vec3(-2,2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object1 = new SceneManager::Object(materialID1, gm->GetStandardCubeGeometryId(), transf1);
	SceneManager::Transform transf2 = SceneManager::Transform(glm::vec3(-2,-2,0), glm::quat(0,-1,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object2 = new SceneManager::Object(materialID2, gm->GetStandardCubeGeometryId(), transf2);
	SceneManager::Transform transf3 = SceneManager::Transform(glm::vec3(2,-2,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	SceneManager::Object* object3 = new SceneManager::Object(materialID3, gm->GetStandardSphereGeometryId(), transf3);
	scene.AddObject(object1);
	scene.AddObject(object2);
	scene.AddObject(object3);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//Lights
	SceneManager::LightBaseParams light1BaseParams;
	light1BaseParams.ambient = glm::vec4(1,1,1,1);
	light1BaseParams.diffuse = glm::vec4(1,1,1,1);
	light1BaseParams.specular = glm::vec4(1,1,1,1);
	SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(glm::vec3(0,0,2), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 5.0f);
	scene.AddPointLight(pointLight1);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

}
}
