#include "FunctionalTest/Material/MaterialFunctionnalTest.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"
#include "Utilities/BrainLoader/BrainLoader.h"
#include "SceneManager/Objects/PointCloud.h"

namespace Atum
{
namespace FunctionnalTest
{

//-----------------------------------------------------------------------------
void PointCloudTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* geometryManager = sceneManager.GetGeometryManager();
	
	// Init cloud points shader
	SceneManager::ShaderListID brainShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_PointCloud_Vertex.vx", "../../data/shaders/GLSL_PointCloud_Fragment.fg", NULL);

	float width = 5.0f;
	float height = 5.0f;
	float depth = 5.0f;
	LowLevelGraphics::ShaderProgram* brainShaderProgram = sceneManager.GetShaderListManager()->GetShaderList(brainShaderID)->GetShaderProgram();

	LowLevelGraphics::LowLevelAPI::BindShaders(sceneManager.GetShaderListManager()->GetShaderList(brainShaderID));

	float value = 1.0f;
	brainShaderProgram->UpdateShaderParameterWithName("pointSize", &value, SHADER_FLOAT);
	value = -width/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("xMin", &value, SHADER_FLOAT);
	value = width/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("xMax", &value, SHADER_FLOAT);
	value = -depth/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("yMin", &value, SHADER_FLOAT);
	value = depth/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("yMax", &value, SHADER_FLOAT);
	value = -height/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("zMin", &value, SHADER_FLOAT);
	value = height/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("zMax", &value, SHADER_FLOAT);
	value = 5.0f;
	brainShaderProgram->UpdateShaderParameterWithName("distanceShellSphere", &value, SHADER_FLOAT);
	value = 2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("distanceViewPlane", &value, SHADER_FLOAT);

	LowLevelGraphics::LowLevelAPI::UnbindShaders();
	
	LowLevelGraphics::GeometryParameters geometryParameters;
	
	Utilities::BrainLoader::CreateBrainGeometry("../../data/models/mr188_t1_pl.nii", width, height, depth, 1, geometryParameters);
	SceneManager::GeometryID brainGeometryID = geometryManager->CreateGeometry(geometryParameters);

	SceneManager::MaterialParameters pointCloudMaterial;
	pointCloudMaterial.phongParam = SceneManager::PhongParameter(glm::vec4(1,1,1,1), glm::vec4(1,1,1,1),glm::vec4(1,1,1,1),10);
	SceneManager::MaterialID brainMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(pointCloudMaterial, brainShaderID);
	
	SceneManager::Transform brainTransform(glm::vec3(0,0,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	Utilities::AABB aabbBrain(glm::vec3(-width/2.0f,-depth/2.0f,-height/2.0f), glm::vec3(width/2.0f,depth/2.0f,height/2.0f));
	SceneManager::PointCloud * pointCloud = new SceneManager::PointCloud(brainMaterialID, brainGeometryID, brainTransform, aabbBrain);

	scene.AddPointCloud(pointCloud);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

//-----------------------------------------------------------------------------
void PointCloudSliceTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* geometryManager = sceneManager.GetGeometryManager();

	// Init cloud points shader
	SceneManager::ShaderListID brainShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_PointCloud_Vertex.vx", "../../data/shaders/GLSL_PointCloud_Fragment.fg", NULL);

	float width = 5.0f;
	float height = 5.0f;
	float depth = 5.0f;
	LowLevelGraphics::ShaderProgram* brainShaderProgram = sceneManager.GetShaderListManager()->GetShaderList(brainShaderID)->GetShaderProgram();

	LowLevelGraphics::LowLevelAPI::BindShaders(sceneManager.GetShaderListManager()->GetShaderList(brainShaderID));

	float value = 1.0f;
	brainShaderProgram->UpdateShaderParameterWithName("pointSize", &value, SHADER_FLOAT);
	value = -width/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("xMin", &value, SHADER_FLOAT);
	value = width/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("xMax", &value, SHADER_FLOAT);
	value = -depth/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("yMin", &value, SHADER_FLOAT);
	value = depth/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("yMax", &value, SHADER_FLOAT);
	value = -height/2.0f;
	brainShaderProgram->UpdateShaderParameterWithName("zMin", &value, SHADER_FLOAT);
	value = 0.0f;
	brainShaderProgram->UpdateShaderParameterWithName("zMax", &value, SHADER_FLOAT);
	value = 1.8f;
	brainShaderProgram->UpdateShaderParameterWithName("distanceShellSphere", &value, SHADER_FLOAT);
	value = 1.5f;
	brainShaderProgram->UpdateShaderParameterWithName("distanceViewPlane", &value, SHADER_FLOAT);

	LowLevelGraphics::LowLevelAPI::UnbindShaders();

	LowLevelGraphics::GeometryParameters geometryParameters;

	Utilities::BrainLoader::CreateBrainGeometry("../../data/models/mr188_t1_pl.nii", width, height, depth, 1, geometryParameters);
	SceneManager::GeometryID brainGeometryID = geometryManager->CreateGeometry(geometryParameters);

	SceneManager::MaterialParameters pointCloudMaterial;
	pointCloudMaterial.phongParam = SceneManager::PhongParameter(glm::vec4(1,1,1,1), glm::vec4(1,1,1,1),glm::vec4(1,1,1,1),10);
	SceneManager::MaterialID brainMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(pointCloudMaterial, brainShaderID);

	SceneManager::Transform brainTransform(glm::vec3(0,0,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	Utilities::AABB aabbBrain(glm::vec3(-width/2.0f,-depth/2.0f,-height/2.0f), glm::vec3(width/2.0f,depth/2.0f,height/2.0f));
	SceneManager::PointCloud * pointCloud = new SceneManager::PointCloud(brainMaterialID, brainGeometryID, brainTransform, aabbBrain);

	scene.AddPointCloud(pointCloud);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(5,5,10), glm::vec3(0,0,0), glm::vec3(0,10,0));
	scene.AddCamera(camera);

	//test shared shader parameter
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* test = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,test,SHADER_MATRIX44);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

}
}
