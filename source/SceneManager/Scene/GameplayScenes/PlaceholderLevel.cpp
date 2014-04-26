#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Objects/GameplayObjects/PlatformCanyon.h"
#include "SceneManager/Level/Level.h"


#define SCROLLING_DISTANCE_PER_FRAME -0.1f

namespace Atum
{
namespace SceneManager
{
	PlaceholderLevel::PlaceholderLevel()
		: m_titleScreenObject(NULL)
		, m_dummyCamera(NULL)
	{
		Init();

		// buffers 3 levels
		m_levels.push_back(new Level());
		m_levels.push_back(new Level());
		m_levels.push_back(new Level());
	}

	//PlaceholderLevel::PlaceholderLevel(const LevelLayout& level)
	//{
	//	Object* platform = new PlatformCanyon(glm::vec4(-1.5, -1.5, 0, 1), glm::vec4(0.1, 1, 1, 1));
	//	((GamePlayObject*)platform)->Init();
	//	AddObject(platform);
	//}

	PlaceholderLevel::~PlaceholderLevel()
	{
		
		Uninit();
	}

	void PlaceholderLevel::Init()
	{
		CreateTitleScreenObject();
		
		auto it = m_levels.begin();
		auto endIt = m_levels.end();
		for (; it != endIt; ++it)
		{
			InitLevel(*it);

		}
	}

	void PlaceholderLevel::Uninit()
	{
		RemoveTitleScreenObject();
	}


	void PlaceholderLevel::CreateTitleScreenObject()
	{
		m_titleScreenObject = new MainCharacter();
		m_titleScreenObject->Init();

		//m_titleScreenObject = new Object(GetMaterial(), GetQuad(), Transform());
		AddObject(m_titleScreenObject);

		PerspectiveCameraParams params(45, 1280/720.0f, 0.1f, 1000.0f);
		m_dummyCamera = new PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

		AddCamera(m_dummyCamera);
		SetCurrentCamera(0);
	}

	void PlaceholderLevel::RemoveTitleScreenObject()
	{
		delete m_titleScreenObject;
		delete m_dummyCamera;
	}

	void PlaceholderLevel::Update()
	{

		auto it = m_levels.begin();
		auto itend = m_levels.end();
		for (; it != itend; ++it)
		{
			(*it)->ScrollSideways(glm::vec4(SCROLLING_DISTANCE_PER_FRAME, 0, 0, 0));
		}

		// Needs to generate a new level if the current one is getting out of the screen.
		if (m_levels.empty() == false && m_levels.front()->GetCurrentPosition().x < -20)
		{
			Level* levelToDel = m_levels.front();
			delete levelToDel;
			m_levels.pop_front();

			Level* level = new Level();
			InitLevel(level);
			m_levels.push_back(level);
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


	Level::Level()
	: m_currentPosition()
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
		params.LevelHeight = 12;
		params.LevelWidth = 256;
		params.PlatformLenghtRange[0] = 4;
		params.PlatformLenghtRange[1] = 16;
		LevelLayoutGenerator levelGen;

		LevelLayout level = levelGen.GenerateLevel(params);


		// Creates the objects and put them in the objectList;
		int currentYPosition = 0;
		float currentXPosition = 0;

		int levelLength = level.GetLength();
		int currentIndex = 0;

		while (currentIndex + 1 < levelLength)
		{
			int currentPlatformLength = 0;

			currentYPosition = level.m_height[currentIndex];
			currentIndex++;
			currentPlatformLength++;

			if (currentIndex < levelLength && level.m_height[currentIndex] == JUMP_LEVEL_ID)
			{
				while (currentIndex < levelLength && level.m_height[currentIndex] == JUMP_LEVEL_ID)
				{
					currentIndex++;
					currentXPosition++;
				}

				currentPlatformLength--;
			}

			currentYPosition = level.m_height[currentIndex];

			while (currentIndex < levelLength && level.m_height[currentIndex] == currentYPosition)
			{
				currentIndex++;
				currentPlatformLength++;
			}
			currentXPosition += currentPlatformLength;

			Object* platform = new PlatformCanyon(glm::vec4(currentXPosition - currentPlatformLength / 2.0f, currentYPosition, 0, 1), glm::vec4(currentPlatformLength, 1, 1, 1));
			((GamePlayObject*)platform)->Init();

			m_objectList.push_back(platform);
		}
	}

} // namespace SceneManager
} // namespace Atum

