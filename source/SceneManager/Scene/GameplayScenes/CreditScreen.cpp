#include "SceneManager/Scene/GameplayScenes/CreditScreen.h"
#include "SceneManager/Scene/GameplayScenes/TitleScreen.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


namespace Atum
{
namespace SceneManager
{
	CreditScreen::CreditScreen()
		:m_titleScreenObject(NULL)
		,m_dummyCamera(NULL)
	{
	}

	CreditScreen::~CreditScreen()
	{
		Uninit();
	}

	void CreditScreen::Init()
	{
		CreateTitleScreenObject();
	}

	void CreditScreen::Uninit()
	{
		RemoveTitleScreenObject();
	}

	TextureId CreditScreen::GetTexture()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/test1.bmp");

		static TextureId titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

		return titleScreenTextureID;
	}

	MaterialID CreditScreen::GetMaterial()
	{
		TextureParameter textureParameter(GetTexture());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,TitleScreen::GetShader());

		return titleScreenMaterialID;
	}

	void CreditScreen::CreateTitleScreenObject()
	{
		m_titleScreenObject = new Object(GetMaterial(), TitleScreen::GetQuad(), Transform());
		AddObject(m_titleScreenObject);
			
		PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
		m_dummyCamera = new PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

		AddCamera(m_dummyCamera);
		SetCurrentCamera(0);
	}

	void CreditScreen::RemoveTitleScreenObject()
	{
		delete m_titleScreenObject;
		delete m_dummyCamera;
	}

} // namespace SceneManager
} // namespace Atum

