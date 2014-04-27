#include "TestSceneLoader.h"
#include "GLM/include/glm/gtc/type_ptr.hpp"
#include "SceneManager/Scene/Scene.h"
//#include "SceneManager/Material/Material.h"
//#include "SceneManager/Objects/Object.h"
//#include "SceneManager/Manager/GeometryManager.h"
//#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"
//#include "SceneManager/Camera/PerspectiveCamera.h"
//#include "SceneManager/Utilities/Transform.h"
//#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
//#include "Utilities/Loader/ObjectLoader.h"
//#include "Utilities/Indexer/Indexer.h"
//#include "Utilities/BrainLoader/BrainLoader.h"
//#include "SceneManager/Objects/PointCloud.h"
//#include "LowLevelGraphics/Context/Context.h"
//#include "SceneManager/Lights/PointLight.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Scene/GameplayScenes/TitleScreen.h"
#include "SceneManager/Scene/GameplayScenes/CreditScreen.h"
#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "../SceneManager/Level/Level.h"
//#include "SceneManager/Objects/Cube.h"
//#include "SceneManager/SkyBox/SkyBox.h"
//#include "ParticleSystem/ParticleSystem.h"
//#include "Utilities/Image/ImageUtilities.h"

//#include "ParticleSystem/Behavior/AccelerationBehavior.h"
//#include "ParticleSystem/Behavior/FollowBehavior.h"
//#include "ParticleSystem/Behavior/OrbitalBehavior.h"
//#include "ParticleSystem/Behavior/AttractorRepulsor.h"
//#include "ParticleSystem/Behavior/FadeBehavior.h"
//#include "ParticleSystem/Behavior/MultiColorBehavior.h"
//#include "ParticleSystem/Behavior/ExplodingSizeBehavior.h"


TestSceneLoader::TestSceneLoader(SceneManager::SceneManager & sceneManager) : m_sceneManager(sceneManager)
{
	Events::EventManager::GetInstance().RegisterKeyboardListener(this);

	SceneManager::Scene* titleScreen = new SceneManager::TitleScreen();
	titleScreen->Init();
	m_sceneManager.AddScene(titleScreen);
	m_sceneManager.SetCurrentScene(0);

	SceneManager::Scene* creditScreen = new SceneManager::CreditScreen();
	creditScreen->Init();
	m_sceneManager.AddScene(creditScreen);

	SceneManager::Scene* placeholder = new SceneManager::PlaceholderLevel();
	placeholder->Init();
	m_sceneManager.AddScene(placeholder);


	////-------------------------------------------------INIT SHADERS---------------------------------------------------------------------------------------------
	//// Init Phong shader
	//SceneManager::ShaderListID phongShaderID = m_sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP);
	//m_sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::PHONG_SHADING);
	//m_sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg",  SceneManager::NO_ILLUMINATION | SceneManager::DIFFUSE_MAP);
	//m_sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::NO_ILLUMINATION);

	//// Init cloud points shader
	//SceneManager::ShaderListID brainShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_PointCloud_Vertex.vx", "../../data/shaders/GLSL_PointCloud_Fragment.fg", NULL);

	//float width = 5.0f;
	//float height = 5.0f;
	//float depth = 5.0f;
	//LowLevelGraphics::ShaderProgram* brainShaderProgram = sceneManager.GetShaderListManager()->GetShaderList(brainShaderID)->GetShaderProgram();

	//LowLevelGraphics::LowLevelAPI::BindShaders(sceneManager.GetShaderListManager()->GetShaderList(brainShaderID));

	//float value = 1.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("pointSize", &value, SHADER_FLOAT);
	//value = -width/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("xMin", &value, SHADER_FLOAT);
	//value = width/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("xMax", &value, SHADER_FLOAT);
	//value = -depth/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("yMin", &value, SHADER_FLOAT);
	//value = depth/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("yMax", &value, SHADER_FLOAT);
	//value = -height/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("zMin", &value, SHADER_FLOAT);
	//value = height/2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("zMax", &value, SHADER_FLOAT);
	//value = 5.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("distanceShellSphere", &value, SHADER_FLOAT);
	//value = 2.0f;
	//brainShaderProgram->UpdateShaderParameterWithName("distanceViewPlane", &value, SHADER_FLOAT);

	//LowLevelGraphics::LowLevelAPI::UnbindShaders();

	//// Init cube map shader
	//SceneManager::ShaderListID cubeMapShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_CubeMap_Vertex_Shader.vx", "../../data/shaders/GLSL_CubeMap_Fragment_Shader.fg", NULL);

	//// Init parallax map shader
	//SceneManager::ShaderListID parallaxMapShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::PHONG_SHADING | SceneManager::DIFFUSE_MAP | SceneManager::PARALLAX_MAP);
	//sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Generic_Vertex_Shader.vx", "../../data/shaders/GLSL_Generic_Fragment_Shader.fg", SceneManager::PHONG_SHADING | SceneManager::PARALLAX_MAP);

	////Init particle shader
	//SceneManager::ShaderListID particleShaderID = sceneManager.GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Particles_Vertex_Shader.vx", "../../data/shaders/GLSL_Particles_Fragment_Shader.fg", NULL);

	////-------------------------------------------------INIT TEXTURES---------------------------------------------------------------------------------------------
	//// Init earth texture
	//Utilities::Image::ImageParameters<unsigned char> earthImage;
	//Utilities::Image::LoadImageFromFile(earthImage, "../../data/textures/Earth_DayMap.bmp");
	//SceneManager::TextureId earthTextureID = sceneManager.GetTextureManager()->CreateTexture(earthImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init fur texture
	//Utilities::Image::ImageParameters<unsigned char> furImage;
	//Utilities::Image::LoadImageFromFile(furImage, "../../data/textures/bunny_texture.bmp");
	//SceneManager::TextureId furTextureID = sceneManager.GetTextureManager()->CreateTexture(furImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init wood texture
	//Utilities::Image::ImageParameters<unsigned char> woodImage;
	//Utilities::Image::LoadImageFromFile(woodImage, "../../data/textures/wood02.bmp");
	//SceneManager::TextureId woodTextureID = sceneManager.GetTextureManager()->CreateTexture(woodImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init motif texture
	//Utilities::Image::ImageParameters<unsigned char> motifImage;
	//Utilities::Image::LoadImageFromFile(motifImage, "../../data/textures/patternWall.bmp");
	//SceneManager::TextureId motifTextureID = sceneManager.GetTextureManager()->CreateTexture(motifImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init grass texture
	//Utilities::Image::ImageParameters<unsigned char> grassImage;
	//Utilities::Image::LoadImageFromFile(grassImage, "../../data/textures/grass.bmp");
	//SceneManager::TextureId grassTextureID = sceneManager.GetTextureManager()->CreateTexture(grassImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);


	//// Init tree texture
	//Utilities::Image::ImageParameters<unsigned char> treeImage;
	//Utilities::Image::LoadImageFromFile(treeImage, "../../data/textures/tree.bmp");
	//SceneManager::TextureId treeTextureID = sceneManager.GetTextureManager()->CreateTexture(treeImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init house texture
	//Utilities::Image::ImageParameters<unsigned char> houseImage;
	//Utilities::Image::LoadImageFromFile(houseImage, "../../data/textures/house.bmp");
	//SceneManager::TextureId houseTextureID = sceneManager.GetTextureManager()->CreateTexture(houseImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init cube map texture
	//std::vector<Utilities::Image::ImageParameters<unsigned char>> imageParameters;
	//imageParameters.resize(6);
	//Utilities::Image::LoadImageFromFile(imageParameters[0], "../../data/textures/skybox/left.bmp");
	//Utilities::Image::LoadImageFromFile(imageParameters[1], "../../data/textures/skybox/right.bmp");
	//Utilities::Image::LoadImageFromFile(imageParameters[2], "../../data/textures/skybox/bottom.bmp");
	//Utilities::Image::LoadImageFromFile(imageParameters[3], "../../data/textures/skybox/top.bmp");
	//Utilities::Image::LoadImageFromFile(imageParameters[4], "../../data/textures/skybox/front.bmp");
	//Utilities::Image::LoadImageFromFile(imageParameters[5], "../../data/textures/skybox/back.bmp");
	//SceneManager::TextureId skyBoxTextureID = sceneManager.GetTextureManager()->CreateTextureSkyBox(imageParameters, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	//// Init parallax map
	//Utilities::Image::ImageParameters<unsigned char> parallaxMapNormal;
	//Utilities::Image::LoadImageFromFile(parallaxMapNormal, "../../data/textures/ParallaxMap.png");
	//SceneManager::TextureId parallaxMapNormalID = sceneManager.GetTextureManager()->CreateTexture(parallaxMapNormal, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

	//Utilities::Image::ImageParameters<unsigned char> parallaxMapTexture;
	//Utilities::Image::LoadImageFromFile(parallaxMapTexture, "../../data/textures/ParallaxTex.bmp");
	//SceneManager::TextureId parallaxMapTextureID = sceneManager.GetTextureManager()->CreateTexture(parallaxMapTexture, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

	////-------------------------------------------------INIT MATERIALS---------------------------------------------------------------------------------------------
	//// Init the bunny material
	//SceneManager::MaterialParameters materialParameters;
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(furTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.3,0.3,0.3,1), glm::vec4(0.3,0.3,0.3,1), glm::vec4(0.5,0.3,0.3,1), 2);
	//SceneManager::MaterialID bunnyMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the earth material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(earthTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0,0,0,1), glm::vec4(1,1,1,1), glm::vec4(0.5,0.5,0.5,1), 60);
	//SceneManager::MaterialID earthMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the wood material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(woodTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.1,0.1,0.1,1), glm::vec4(1,1,1,1), glm::vec4(0.5,0.3,0.3,1), 10);
	//SceneManager::MaterialID woodMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the motif material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(motifTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0,0,0.2,1), glm::vec4(0.8,1,1,1), glm::vec4(0.3,0.3,0.3,1), 1);
	//SceneManager::MaterialID motifMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the grass material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(grassTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.5,0.5,0.5,1), glm::vec4(0.7,0.7,0.8,1), glm::vec4(0.1,0.1,0.1,1), 1);
	//SceneManager::MaterialID grassMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the house material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(houseTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.5,0.5,0.5,1), glm::vec4(0.8,0.8,0.8,1), glm::vec4(0,0,0,1), 160);
	//SceneManager::MaterialID houseMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the tree material
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(treeTextureID);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.5,0.5,0.5,1), glm::vec4(0.7,0.7,0.8,1), glm::vec4(0.1,0.1,0.1,1), 1);
	//SceneManager::MaterialID treeMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, phongShaderID);

	//// Init the skybox material
	//materialParameters.phongParam.m_isActive = false;
	//materialParameters.skyBoxParam = SceneManager::TextureParameter(skyBoxTextureID);
	//materialParameters.diffuseMapParam.m_isActive = false;
	//SceneManager::MaterialID skyBoxMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, cubeMapShaderID);

	//// Init the brain material
	//materialParameters.diffuseMapParam.m_textID = 0;
	//materialParameters.diffuseMapParam.m_isActive = false;
	//SceneManager::MaterialID brainMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, brainShaderID);

	//// Init the parallax map material
	//materialParameters.skyBoxParam.m_isActive = false;
	//materialParameters.diffuseMapParam = SceneManager::TextureParameter(parallaxMapTextureID);
	//materialParameters.parallaxParam = SceneManager::ParallaxMapParameters(parallaxMapNormalID,0.045,0.0);
	//materialParameters.phongParam = SceneManager::PhongParameter(glm::vec4(0.3,0.3,0.3,1), glm::vec4(0.5,0.5,0.5,1), glm::vec4(0.6,0.7,0.7,1), 2);
	//SceneManager::MaterialID parallaxMapMaterialID = sceneManager.GetMaterialManager()->CreateMaterial(materialParameters, parallaxMapShaderID);
	////-------------------------------------------------INIT GEOMETRY---------------------------------------------------------------------------------------------
	//SceneManager::GeometryManager* const geometryManager = m_sceneManager.GetGeometryManager();
	//std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals;
	//LowLevelGraphics::GeometryParameters geometryParameters;

	//// Init the bunny geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/BunnyUV.obj", vertices, uvs);
	//Utilities::Indexer::GenerateInterpolatedNormals(vertices, uvs, geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int bunnyGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//// Init the floor geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/floor.obj", vertices, normals, uvs);
	//Utilities::Indexer::IndexVertexUvNormal(vertices, uvs, normals, geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int floorGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//// Init the house geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/house.obj", vertices, normals, uvs);
	//Utilities::Indexer::IndexVertexUvNormal(vertices, uvs, normals, geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int houseGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//// Init the mountain geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/mountain.obj", vertices, normals, uvs);
	//Utilities::Indexer::GenerateInterpolatedNormals(vertices, uvs,  geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int mountainGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//// Init the wall geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/wall.obj", vertices, normals, uvs);
	//Utilities::Indexer::IndexVertexUvNormal(vertices, uvs, normals,  geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int wallGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//// Init the tree geometry
	//Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/tree.obj", vertices, normals, uvs);
	//Utilities::Indexer::GenerateInterpolatedNormals(vertices, uvs,  geometryParameters.index, geometryParameters.position, geometryParameters.textureCoordinates, geometryParameters.normal);

	//unsigned int treeGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//Utilities::BrainLoader::CreateBrainGeometry("../../data/models/T1.nii", width, height, depth, 1, geometryParameters);
	//SceneManager::GeometryID brainGeometryID = geometryManager->CreateGeometry(geometryParameters);

	//geometryParameters.index.clear();
	//geometryParameters.position.clear(); vertices.clear();
	//geometryParameters.normal.clear(); normals.clear();
	//geometryParameters.textureCoordinates.clear(); uvs.clear();

	//geometryParameters = Utilities::CreateSkyBoxGeometry(3000.0f);
	//SceneManager::GeometryID skyBoxGeometryID = geometryManager->CreateGeometry(geometryParameters);

	////-------------------------------------------------INIT PARTICLE SYSTEMS---------------------------------------------------------------------------------------------

	////Particle system parameters
	//ParticleSystem::ParticleSystemParameters parameters;
	//parameters.emitPosition = glm::vec3(1.5f,0.7f,-0.6f);
	//parameters.offsetRadius = 0.6f;
	//parameters.colorRange[0] = glm::vec4(0.4f, 0.1f, 0.3f, 0.7f);
	//parameters.colorRange[1] = glm::vec4(0.2f, 0.14f, 0.66f, 0.6f);
	//parameters.particleSizeRange[0] = 4.0f;
	//parameters.particleSizeRange[1] = 6.0f;
	//parameters.velocityRange[0] = 2.4f;
	//parameters.velocityRange[1] = 3.4f;
	//parameters.orientationRange[0] = glm::vec3(-1.0f,-1.0f,-1.0f);
	//parameters.orientationRange[1] = glm::vec3(1.0f,1.0f,1.0f);
	//parameters.lifespanRange[0] = 1.0f;
	//parameters.lifespanRange[1] = 3.0f;
	//parameters.shaderListID = particleShaderID;

	////Behaviors
	//unsigned int nbParticleBatches = 100;
	//unsigned int nbTargetParticles = 100000;
	//unsigned int nbMaxParticles = 500000;
	//ParticleSystem::Behavior* behavior = new ParticleSystem::AccelerationBehavior(0.0f,1/2.0f,nbParticleBatches);
	//parameters.behaviors.push_back(behavior);
	//std::vector<ParticleSystem::AttractorRepulsor> attractors;
	//attractors.push_back(ParticleSystem::AttractorRepulsor(parameters.emitPosition+glm::vec3(2.0f,2.0f,2.0f),140.0f));
	//attractors.push_back(ParticleSystem::AttractorRepulsor(parameters.emitPosition-glm::vec3(2.0f,2.0f,2.0f),140.0f));

	////ParticleSystem::Behavior* behavior = new ParticleSystem::FollowBehavior(attractors);
	////parameters.behaviors.push_back(behavior);
	//behavior = new ParticleSystem::FadeBehavior();
	//parameters.behaviors.push_back(behavior);
	//behavior = new ParticleSystem::MultiColorBehavior(nbParticleBatches);
	//parameters.behaviors.push_back(behavior);
	//behavior = new ParticleSystem::OrbitalBehavior(attractors);
	//parameters.behaviors.push_back(behavior);
	//behavior = new ParticleSystem::ExplodingSizeBehavior();
	//parameters.behaviors.push_back(behavior);

	//ParticleSystem::ParticleSystem* particleSystem = new ParticleSystem::ParticleSystem(parameters, nbMaxParticles, nbTargetParticles, nbParticleBatches);

	////-------------------------------------------------INIT SCENES---------------------------------------------------------------------------------------------
	//// camera
	//SceneManager::PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
	//SceneManager::Camera* camera = new SceneManager::PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

	//// Update camera parameters
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX,&camera->GetViewMatrix(),SHADER_MATRIX44);

	//glm::mat4x4* projectionMatrix = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX,projectionMatrix,SHADER_MATRIX44);

	//// Lights
	//SceneManager::LightBaseParams light1BaseParams;
	//light1BaseParams.ambient = glm::vec4(0.3,0.3,0.3,1);
	//light1BaseParams.diffuse = glm::vec4(1,1,1,1);
	//light1BaseParams.specular = glm::vec4(1,1,1,1);
	//SceneManager::LightBaseParams light2BaseParams;
	//light2BaseParams.ambient = glm::vec4(0,0,0,1);
	//light2BaseParams.diffuse = glm::vec4(1,1,1,1);
	//light2BaseParams.specular = glm::vec4(1,1,1,1);
	//SceneManager::LightBaseParams light3BaseParams;
	//light3BaseParams.ambient = glm::vec4(1,1,1,1);
	//light3BaseParams.diffuse = glm::vec4(1,1,1,1);
	//light3BaseParams.specular = glm::vec4(1,1,1,1);

	//SceneManager::PointLight* pointLight1 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(glm::vec3(-10,10,-10), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);
	//SceneManager::PointLight* pointLight2 = new SceneManager::PointLight(light2BaseParams, SceneManager::Transform(glm::vec3(10,10,10), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);
	//SceneManager::PointLight* pointLight3 = new SceneManager::PointLight(light3BaseParams, SceneManager::Transform(glm::vec3(100,100,100), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);
	//SceneManager::PointLight* pointLight4 = new SceneManager::PointLight(light1BaseParams, SceneManager::Transform(glm::vec3(2.78,-2.4,5.11), glm::quat(1,0,0,0), glm::vec3(1,1,1)), 1);

	////-------------------------------------------------INIT FIRST SCENE---------------------------------------------------------------------------------------------
	//SceneManager::Scene * scene = new SceneManager::Scene();
	//SceneManager::Object * object;
	//object = new SceneManager::Object(bunnyMaterialID, bunnyGeometryID, SceneManager::Transform(glm::vec3(0,-0.80f,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));

	//scene->AddObject(object);
	//object = new SceneManager::Object(earthMaterialID, geometryManager->GetStandardSphereGeometryId(), SceneManager::Transform(glm::vec3(-3,0.20f,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));

	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(3,0,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Object(motifMaterialID, floorGeometryID, SceneManager::Transform(glm::vec3(0,-1.0f,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Object(motifMaterialID, wallGeometryID, SceneManager::Transform(glm::vec3(0,-1.0f,-8.5f), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//m_sceneManager.AddScene(scene);
	//m_sceneManager.SetCurrentScene(0);

	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);

	//scene->AddPointLight(pointLight1);
	//scene->AddPointLight(pointLight2);

	////-------------------------------------------------INIT SECOND SCENE---------------------------------------------------------------------------------------------
	//scene = new SceneManager::Scene();
	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);

	//SceneManager::Transform brainTransform(glm::vec3(0,0,0), glm::quat(1,0,0,0), glm::vec3(1,1,1));
	//Utilities::AABB aabbBrain(glm::vec3(-width/2.0f,-depth/2.0f,-height/2.0f), glm::vec3(width/2.0f,depth/2.0f,height/2.0f));
	//SceneManager::PointCloud * pointCloud = new SceneManager::PointCloud(brainMaterialID, brainGeometryID, brainTransform, aabbBrain);

	//scene->AddPointCloud(pointCloud);

	//m_sceneManager.AddScene(scene);

	////-------------------------------------------------INIT THIRD SCENE---------------------------------------------------------------------------------------------
	//scene = new SceneManager::Scene();
	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);

	//object = new SceneManager::Object(houseMaterialID, houseGeometryID, SceneManager::Transform(glm::vec3(3.11f,1.71f,15.0f), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Object(grassMaterialID, mountainGeometryID, SceneManager::Transform(glm::vec3(7.75f,0,-12.45f), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);
	//object = new SceneManager::Object(treeMaterialID, treeGeometryID, SceneManager::Transform(glm::vec3(14.75f,5.5f,0), glm::quat(1,0,0,0), glm::vec3(2,2,2)));
	//scene->AddObject(object);
	//object = new SceneManager::Object(treeMaterialID, treeGeometryID, SceneManager::Transform(glm::vec3(14.75f,0.0f,20.0f), glm::quat(1,0,0,0), glm::vec3(2,2,2)));
	//scene->AddObject(object);
	//object = new SceneManager::Object(treeMaterialID, treeGeometryID, SceneManager::Transform(glm::vec3(-15,0.0f,20.0f), glm::quat(1,0,0,0), glm::vec3(2,2,2)));
	//scene->AddObject(object);

	//scene->AddSkyBox(new SceneManager::SkyBox(skyBoxMaterialID, skyBoxGeometryID));

	//scene->AddPointLight(pointLight3);

	//m_sceneManager.AddScene(scene);

	////-------------------------------------------------INIT FOURTH SCENE---------------------------------------------------------------------------------------------
	//scene = new SceneManager::Scene();

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(3,7,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(0,10,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(-3,12,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(2,13,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(0,30,1), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(-4,14,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(3,16,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(0,18,0), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(-3,15,3), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(3,20,-4), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(3,23,-3), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//object = new SceneManager::Cube(woodMaterialID, SceneManager::Transform(glm::vec3(-3,25,3), glm::quat(1,0,0,0), glm::vec3(1,1,1)));
	//scene->AddObject(object);

	//m_sceneManager.AddScene(scene);

	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);

	//scene->AddPointLight(pointLight1);
	//scene->AddPointLight(pointLight2);

	//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();

	////-------------------------------------------------INIT FIFTH SCENE---------------------------------------------------------------------------------------------
	//scene = new SceneManager::Scene();
	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);

	//object = new SceneManager::Object(parallaxMapMaterialID, geometryManager->GetStandardPlaneGeometryId(), SceneManager::Transform(glm::vec3(-0.2,-0.6f,-1.0), glm::quat(-0.21,-0.08,0.01,0.97), glm::vec3(3,3,1)));
	//scene->AddObject(object);

	//scene->AddPointLight(pointLight4);

	//m_sceneManager.AddScene(scene);

	//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();

	////-------------------------------------------------INIT SIXTH SCENE---------------------------------------------------------------------------------------------
	//scene = new SceneManager::Scene();
	//scene->AddCamera(camera);
	//scene->SetCurrentCamera(0);
	//scene->AddParticleSystem(particleSystem);
	//m_sceneManager.AddScene(scene);
}

TestSceneLoader::~TestSceneLoader()
{

}

void TestSceneLoader::NotifyKeyPressed(const Events::KeyboardEvent& event)
{
	if(event.GetEventType() == Events::KeyboardEventType::KEY_PRESSED)
	{
		if (event.GetKey() == '1')
		{
			m_sceneManager.SetCurrentScene(0);
			//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();
		}
		else if (event.GetKey() == '2')
		{
			m_sceneManager.SetCurrentScene(1);
			//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();
		}
		else if (event.GetKey() == '3')
		{
			m_sceneManager.SetCurrentScene(2);
			//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();
		}
		//else if (event.GetKey() == '4')
		//{
		//	m_sceneManager.SetCurrentScene(3);
		//	//m_sceneManager.GetCurrentScene()->UpdateAllPointLights();
		//}
		//else if (event.GetKey() == '5')
		//{
		//	m_sceneManager.SetCurrentScene(4);
		//	m_sceneManager.GetCurrentScene()->UpdateAllPointLights();
		//}
		//else if (event.GetKey() == '6')
		//{
		//	m_sceneManager.SetCurrentScene(5);
		//}
	}
}
