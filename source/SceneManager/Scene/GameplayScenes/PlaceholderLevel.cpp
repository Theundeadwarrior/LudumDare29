#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Objects/GameplayObjects/PlatformCanyon.h"
#include "SceneManager/Objects/GameplayObjects/PlatformRuins.h"
#include "SceneManager/Level/Level.h"
#include "../../Objects/GameplayObjects/PlatformBridge.h"

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
			params.PlatformLenghtRange[0] = 8;
			params.PlatformLenghtRange[1] = 24;
			params.IsUnderGround = false;
		}
		else
		{
			params.LevelHeight = 12;
			params.LevelWidth = 256;
			params.PlatformLenghtRange[0] = 8;
			params.PlatformLenghtRange[1] = 24;
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

