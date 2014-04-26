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
	TitleScreen::TitleScreen()
		:m_alphaTexturedQuadShaderID(0)
		,m_titleScreenTextureID(0)
		,m_titleScreenQuadID(0)
		,m_titleScreenMaterialID(0)
		,m_titleScreenObject(NULL)
		,m_dummyCamera(NULL)
	{
	}

	TitleScreen::~TitleScreen()
	{
		Uninit();
	}

	void TitleScreen::Init()
	{
		LoadShader();
		LoadTexture();
		LoadQuad();
		LoadMaterial();

		CreateTitleScreenObject();
	}

	void TitleScreen::Uninit()
	{
		UnloadMaterial();
		UnloadQuad();
		UnloadTexture();
		UnloadShader();

		RemoveTitleScreenObject();
	}

	void TitleScreen::LoadShader()
	{
		m_alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/FullScreenAlphaTestedTexture.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);
	}

	void TitleScreen::LoadTexture()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/TitleScreen.bmp");
		m_titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);
	}

	void TitleScreen::LoadQuad()
	{
		m_titleScreenQuadID = SceneManager::GetInstance().GetGeometryManager()->CreateGeometry(Utilities::CreatePlaneGeometry(1.0f,1.0f));
	}

	void TitleScreen::LoadMaterial()
	{
		TextureParameter textureParameter(m_titleScreenTextureID);
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		m_titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,m_alphaTexturedQuadShaderID);
	}

	void TitleScreen::UnloadShader()
	{
		SceneManager::GetInstance().GetShaderListManager()->RemoveShaderList(m_alphaTexturedQuadShaderID);
	}

	void TitleScreen::UnloadTexture()
	{
		SceneManager::GetInstance().GetTextureManager()->RemoveTexture(m_titleScreenTextureID);
	}

	void TitleScreen::UnloadQuad()
	{
		SceneManager::GetInstance().GetGeometryManager()->RemoveGeometry(m_titleScreenQuadID);
	}

	void TitleScreen::UnloadMaterial()
	{
		SceneManager::GetInstance().GetMaterialManager()->RemoveMaterial(m_titleScreenMaterialID);
	}

	void TitleScreen::CreateTitleScreenObject()
	{
		m_titleScreenObject = new Object(m_titleScreenMaterialID, m_titleScreenQuadID, Transform());
		AddObject(m_titleScreenObject);
			
		PerspectiveCameraParams params(45, 1024/768.0f, 0.1f, 1000.0f);
		m_dummyCamera = new PerspectiveCamera(params, glm::vec3(0,5,5), glm::vec3(0,0,-1), glm::vec3(0,5,-5));

		AddCamera(m_dummyCamera);
		SetCurrentCamera(0);
	}

	void TitleScreen::RemoveTitleScreenObject()
	{
		delete m_titleScreenObject;
		delete m_dummyCamera;
	}

} // namespace SceneManager
} // namespace Atum

