#include "FunctionalTest/Geometry/GeometryFunctionnalTest.h"
#include "FunctionalTest/FunctionnalTestIncludePackage.h"
#include "Utilities/Loader/ObjectLoader.h"
#include "Utilities/Indexer/Indexer.h"

namespace Atum
{
namespace FunctionnalTest
{

//-----------------------------------------------------------------------------
void GeometryLoaderTest(SceneManager::Scene& scene)
{
	SceneManager::SceneManager& sceneManager = SceneManager::SceneManager::GetInstance();
	SceneManager::GeometryManager* const geometryManager = sceneManager.GetGeometryManager();

	// only need phong and diffuse for normal and uv testing
	SceneManager::ShaderListID phongShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP);

	// Init wood texture
	Utilities::Image::ImageParameters<unsigned char> woodImage;
	Utilities::Image::LoadImageFromFile(woodImage, "../../data/textures/wood02.bmp");
	SceneManager::TextureId woodTextureID = sceneManager.GetTextureManager()->CreateTexture(woodImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	// Init the bunny material
	SceneManager::MaterialParameters materialParameters;
	materialParameters.diffuseMapParam = SceneManager::TextureParameter(woodTextureID);
	materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.3,0.3,0.3,1), glm::vec4(0.9,0.9,0.9,1), glm::vec4(0.5,0.3,0.3,1), 40);
	SceneManager::MaterialID bunnyMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	// Init the bunny geometry
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	LowLevelGraphics::GeometryParameters geometryParameters;

	Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/BunnyUV.obj", vertices, uvs);
	Utilities::Indexer::GenerateInterpolatedNormals(vertices, uvs, geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	unsigned int bunnyGeometryID = geometryManager->CreateGeometry(geometryParameters);

	// camera
	SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

	// Update camera parameters
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	glm::mat4x4* projectionMatrix = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,projectionMatrix,SHADER_MATRIX44);

	// Lights
	SceneManager::LightBaseParams light1BaseParams;
	light1BaseParams.ambient = glm::vec4(0.3,0.3,0.3,1);
	light1BaseParams.diffuse = glm::vec4(1,1,1,1);
	light1BaseParams.specular = glm::vec4(1,1,1,1);
	SceneManager::LightBaseParams light2BaseParams;
	light2BaseParams.ambient = glm::vec4(0,0,0,1);
	light2BaseParams.diffuse = glm::vec4(1,1,1,1);
	light2BaseParams.specular = glm::vec4(1,1,1,1);

	SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(glm::vec3(-10,10,-10), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);
	SceneManager::PointLight* pointLight2 = new SceneManager::PointLight(light2BaseParams, SceneManager::Transform(glm::vec3(10,10,10), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);

	SceneManager::Object * object;
	object = new SceneManager::Object(bunnyMaterialID, bunnyGeometryID, SceneManager::Transform(glm::vec3(0,-0.80f,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));

	scene.AddObject(object);

	sceneManager.AddScene(&scene);
	sceneManager.SetCurrentScene(0);

	scene.AddCamera(camera);
	scene.SetCurrentCamera(0);

	scene.AddPointLight(pointLight1);
	scene.AddPointLight(pointLight2);

	//toremove once we have macros disabling ui in graphics engine
	UserInterface::UiManager::GetInstance().DisableCompleteUi();
}

}
}
