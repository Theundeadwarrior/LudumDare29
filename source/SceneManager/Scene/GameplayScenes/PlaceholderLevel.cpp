#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Objects/GameplayObjects/PlatformCanyon.h"
#include "SceneManager/Objects/GameplayObjects/PlatformRuins.h"
#include "SceneManager/Level/Level.h"
#include "SceneManager/Manager/SoundManager.h"
#include "SceneManager/Objects/GameplayObjects/PlatformBridge.h"
#include "SceneManager/Manager/TypedefID.h"
#include "ParticleSystem/ParticleSystem.h"
#include "ParticleSystem/Behavior/AccelerationBehavior.h"
#include "ParticleSystem/Behavior/AttractorRepulsor.h"
#include "ParticleSystem/Behavior/FadeBehavior.h"
#include "ParticleSystem/Behavior/OrbitalBehavior.h"
#include "ParticleSystem/Behavior/MultiColorBehavior.h"
#include "ParticleSystem/Behavior/FollowBehavior.h"
#include "ParticleSystem/Behavior/ExplodingSizeBehavior.h"

#define SCROLLING_DISTANCE_PER_FRAME -0.2f
#define POSITION_TO_DELETE -148.0F
#define POSITION_TO_SPAWN 108.0F
#define POSITION_FIRST_SPAWN (POSITION_TO_SPAWN - 128.0F)
#define SURFACE_HEIGHT_POSITION -20.0f
#define DEATH_HEIGHT -40.0f

namespace Atum
{
namespace SceneManager
{
	PlaceholderLevel::PlaceholderLevel()
		: m_mainCharacter(NULL)
		, m_background(NULL)
		, m_movingBackground(NULL)
		, m_dummyCamera(NULL)
		, m_switchMusic(false)
	{
		m_currentLevel = new Level();
		m_nextLevel = new Level();
	}

	PlaceholderLevel::~PlaceholderLevel()
	{
		Uninit();
	}

	void PlaceholderLevel::Init()
	{
		m_foreground = new Foreground();
		m_foreground->Init();

		AddObject(m_foreground);

		CreateTitleScreenObject();

		InitLevel(m_currentLevel);
		InitLevel(m_nextLevel);

		m_movingBackground = new MovingBackground();
		m_movingBackground->Init();

		AddObject(m_movingBackground);

		m_background = new Background();
		m_background->Init();

		AddObject(m_background);

		ResetLevelsPosition();

		// Testing particle systems:
		InitParticleSystem();
	}

	void PlaceholderLevel::InitParticleSystem()
	{
		////-------------------------------------------------INIT PARTICLE SYSTEMS---------------------------------------------------------------------------------------------
		ShaderListID particleShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/GLSL_Particles_Vertex_Shader.vx", "../../data/shaders/GLSL_Particles_Fragment_Shader.fg", NULL);
		//Particle system parameters
		ParticleSystem::ParticleSystemParameters parameters;
		parameters.emitPosition = glm::vec3(-0.4f,0.0f,2.0f);
		parameters.offsetRadius = 10.0f;
		parameters.colorRange[0] = glm::vec4(0.0f, 0.44f, 0.86f, 0.1f);
		parameters.colorRange[1] = glm::vec4(1.0f, 1.0f, 1.0f, 0.4f);
		parameters.particleSizeRange[0] = 10.0f;
		parameters.particleSizeRange[1] = 20.0f;
		parameters.velocityRange[0] = 0.3f;
		parameters.velocityRange[1] = 0.5f;
		parameters.orientationRange[0] = glm::vec3(-1.0f,-1.0f,-0.5f);
		parameters.orientationRange[1] = glm::vec3(1.0f,1.0f,0.5f);
		parameters.lifespanRange[0] = 1.0f;
		parameters.lifespanRange[1] = 4.0f;
		parameters.shaderListID = particleShaderID;

		////Behaviors
		unsigned int nbParticleBatches = 20;
		unsigned int nbTargetParticles = 200;
		unsigned int nbMaxParticles = 400;
		ParticleSystem::Behavior* behavior = new ParticleSystem::AccelerationBehavior(0.0f,2.0f,nbParticleBatches);
		parameters.behaviors.push_back(behavior);
		std::vector<ParticleSystem::AttractorRepulsor> attractors;
		attractors.push_back(ParticleSystem::AttractorRepulsor(parameters.emitPosition+glm::vec3(2.0f,2.0f,2.0f),80.0f));
		attractors.push_back(ParticleSystem::AttractorRepulsor(parameters.emitPosition-glm::vec3(2.0f,2.0f,2.0f),140.0f));

		behavior = new ParticleSystem::FollowBehavior(attractors);
		parameters.behaviors.push_back(behavior);
		behavior = new ParticleSystem::FadeBehavior();
		parameters.behaviors.push_back(behavior);
		behavior = new ParticleSystem::MultiColorBehavior(nbParticleBatches);
		parameters.behaviors.push_back(behavior);

		ParticleSystem::ParticleSystem* particleSystem = new ParticleSystem::ParticleSystem(parameters, nbMaxParticles, nbTargetParticles, nbParticleBatches);
		m_particleSystemList.push_back(particleSystem);
	}

	void PlaceholderLevel::ResetLevelsPosition()
	{
		// HACKATHON!!! 
		m_currentLevel->Translate(glm::vec4(POSITION_FIRST_SPAWN, m_currentLevel->GetLastPlatformYPosition() - m_nextLevel->GetFirstPlatformYPosition(), 0, 0));
		m_nextLevel->Translate(glm::vec4(POSITION_TO_SPAWN, m_currentLevel->GetLastPlatformYPosition() - m_nextLevel->GetFirstPlatformYPosition(), 0, 0));
	}

	void PlaceholderLevel::Uninit()
	{
		delete m_mainCharacter;
		delete m_background;
		delete m_movingBackground;
		delete m_foreground;
		delete m_dummyCamera;
	}


	void PlaceholderLevel::CreateTitleScreenObject()
	{
		m_mainCharacter = new MainCharacter();
		m_mainCharacter->Init();

		AddObject(m_mainCharacter);

		PerspectiveCameraParams params(45, 1280/720.0f, 0.1f, 1000.0f);
		m_dummyCamera = new PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

		AddCamera(m_dummyCamera);
		SetCurrentCamera(0);
	}

	void PlaceholderLevel::Update()
	{
		if(m_mainCharacter->GetCharacterState() != GamePlayObject::WallStop)
		{
			m_background->Move();
			m_movingBackground->Move();
			m_foreground->Move();

			m_currentLevel->Translate(glm::vec4(SCROLLING_DISTANCE_PER_FRAME, 0, 0, 0));
			m_nextLevel->Translate(glm::vec4(SCROLLING_DISTANCE_PER_FRAME, 0, 0, 0));

			// Needs to generate a new level if the current one is getting out of the screen.
			if (m_currentLevel->GetPosition().x < POSITION_TO_DELETE)
			{
				// Are we currently beneath the surface?
 				bool isBeneath = m_currentLevel->IsUnderGround();
				Level* levelToDel = m_currentLevel;
				m_currentLevel = m_nextLevel;
				delete levelToDel;

				m_nextLevel = new Level(isBeneath);
				InitLevel(m_nextLevel);
				m_nextLevel->Translate(glm::vec4(POSITION_TO_SPAWN, m_currentLevel->GetLastPlatformYPosition() - m_nextLevel->GetFirstPlatformYPosition(), 0, 0));
			}

			// Might have to switch level if we fall down
			if (m_mainCharacter->GetPosition().y < SURFACE_HEIGHT_POSITION && m_currentLevel->IsUnderGround() == false)
			{
  				GoBeneathTheSurface();
			}

			if (m_mainCharacter->GetPosition().y < DEATH_HEIGHT)
			{
				delete m_currentLevel;
				delete m_nextLevel;
				m_mainCharacter->SetCharacterState(GamePlayObject::Dead);

				// reset level - HOLY COW SO MUCH HAAAAAAAAXXXXX
				m_currentLevel = new Level();
				m_nextLevel = new Level();

				InitLevel(m_currentLevel);
				InitLevel(m_nextLevel);

				ResetLevelsPosition();

				m_mainCharacter->Reset();

				SceneManager::GetInstance().SetCurrentScene(1); // GameOver Screen (so testsceneloader can manage space on screen)
			}
		}

		if(m_switchMusic)
		{
			m_switchMusic = SoundManager::GetInstance().IncrementSwitchMusic(true);
		}

		// Calls the update on base class for updating all objects
		Scene::Update();
	}

	void PlaceholderLevel::InitLevel(Level* level)
	{
		std::list<Object*> objects;
		level->BuildObjectsFromLevelLayout();

		auto itObj = level->GetObjectListBegin();
		auto endItObj = level->GetObjectListEnd();
		for (; itObj != endItObj; ++itObj)
		{
			AddObject(*itObj);
		}
	}

	void PlaceholderLevel::GoBeneathTheSurface()
	{
		// We need to generate new levels for the underworld and delete the old ones (surface world).
		delete m_currentLevel;
		delete m_nextLevel;

		m_currentLevel = new Level(true);
		m_nextLevel = new Level(true);

		InitLevel(m_currentLevel);
		InitLevel(m_nextLevel);

		// HACKATHON!!! 
		m_currentLevel->Translate(glm::vec4(POSITION_FIRST_SPAWN, m_currentLevel->GetLastPlatformYPosition() - m_nextLevel->GetFirstPlatformYPosition() - 26, 0, 0));
 		m_nextLevel->Translate(glm::vec4(POSITION_TO_SPAWN, m_currentLevel->GetLastPlatformYPosition() - m_nextLevel->GetFirstPlatformYPosition(), 0, 0));

 		m_mainCharacter->GoBeneathTheSurface();

		//throw std::exception("The method or operation is not implemented.");

		m_switchMusic = true;
	}


	Level::Level(bool isUnderGround)
    : m_currentPosition()
	, m_isUnderGround(isUnderGround)
	{

	}


	Level::~Level()
	{
		auto it = m_objectList.begin();
		auto endIt = m_objectList.end();

		for (; it != endIt; ++it)
		{
			(*it)->SetState(Object::E_ToDelete);
		}

	}

	void Level::BuildObjectsFromLevelLayout()
	{
		// Generate parameters and layout
		LevelLayoutGenerator::Parameters params;
		if (IsUnderGround() == false)
		{
			params.LevelHeight = 12;
			params.LevelWidth = 256;
			params.PlatformLenghtRange[0] = 6;
			params.PlatformLenghtRange[1] = 16;
			params.IsUnderGround = false;
		}
		else
		{
			params.LevelHeight = 12;
			params.LevelWidth = 256;
			params.PlatformLenghtRange[0] = 4;
			params.PlatformLenghtRange[1] = 12;
			params.IsUnderGround = true;
		}

		LevelLayoutGenerator levelGen(params);


		LevelLayout level = levelGen.GenerateLevel();


		auto it = level.m_platforms.begin();
		auto endit = level.m_platforms.end();

		float currentXPosition = 0;

		for (; it < endit; ++it)
		{
			float platformLength = it->Length;
			float platformHeight = it->Height;

			if (it->Type == PlatformInfo::E_Canyon)
			{
				Object* platform = new PlatformCanyon(glm::vec4(currentXPosition + platformLength / 2.0f, platformHeight - 8, 0, 0)*0.5f, glm::vec4(platformLength*0.5f, 0.5f, 1, 1));
				((GamePlayObject*)platform)->Init();
				m_objectList.push_back(platform);
			}
			else if (it->Type == PlatformInfo::E_Ruins)
			{
				Object* platform = new PlatformRuins(glm::vec4(currentXPosition + platformLength / 2.0f, platformHeight - 8, 0, 0)*0.5f, glm::vec4(platformLength*0.5f, 0.5f, 1, 1));
				((GamePlayObject*)platform)->Init();
				m_objectList.push_back(platform);
			}
			else if (it->Type == PlatformInfo::E_Bridge)
			{
				Object* platform = new PlatformBridge(glm::vec4(currentXPosition + platformLength / 2.0f, platformHeight - 8, 0, 0)*0.5f, glm::vec4(platformLength*0.5f, 0.5f, 1, 1));
				((GamePlayObject*)platform)->Init();
				m_objectList.push_back(platform);
			}

			currentXPosition += platformLength;
		}
	}

	void Level::Translate(const glm::vec4& translation)
	{
		m_currentPosition += translation;

		auto it = m_objectList.begin();
		auto itend = m_objectList.end();
		for (; it != itend; ++it)
		{
			((GamePlayObject*)*it)->SetRelativeXY(translation.x, translation.y);
		}
	}

	float Level::GetLastPlatformYPosition()
	{
		return m_objectList.empty() ? 0 : ((GamePlayObject*)m_objectList.back())->GetPosition().y;
	}

	float Level::GetFirstPlatformYPosition()
	{
		return m_objectList.empty() ? 0 : ((GamePlayObject*)m_objectList.front())->GetPosition().y;
	}


} // namespace SceneManager
} // namespace Atum

