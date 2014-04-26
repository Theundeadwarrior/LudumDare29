#include "SceneManager/Scene/GameplayScenes/PlaceholderLevel.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


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
		//	
		PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
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

