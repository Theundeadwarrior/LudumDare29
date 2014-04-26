#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Objects/GameplayObjects/PlatformCanyon.h"
#include "SceneManager/Level/Level.h"


namespace Atum
{
namespace SceneManager
{
	PlaceholderLevel::PlaceholderLevel()
		:m_titleScreenObject(NULL)
		,m_dummyCamera(NULL)
	{
		Init();
	}

	PlaceholderLevel::PlaceholderLevel(const Level& level)
	{
		int currentYPosition = 0;
		float currentXPosition = 0;

		int levelLength = level.GetLength();
		int currentIndex = 0;

		while (currentIndex +1 < levelLength)
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
			AddObject(platform);
		}

		Object* platform = new PlatformCanyon(glm::vec4(-1.5, -1.5, 0, 1), glm::vec4(0.1, 1, 1, 1));
		((GamePlayObject*)platform)->Init();
		AddObject(platform);
	}

	PlaceholderLevel::~PlaceholderLevel()
	{
		Uninit();
	}

	void PlaceholderLevel::Init()
	{
		CreateTitleScreenObject();
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

} // namespace SceneManager
} // namespace Atum

