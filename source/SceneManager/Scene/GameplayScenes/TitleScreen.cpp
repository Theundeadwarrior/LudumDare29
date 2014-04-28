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
		:m_titleScreenObject(NULL)
		,m_dummyCamera(NULL)
	{
	}

	TitleScreen::~TitleScreen()
	{
		Uninit();
	}

	void TitleScreen::Init()
	{
		CreateTitleScreenObject();
	}

	void TitleScreen::Uninit()
	{
		RemoveTitleScreenObject();
	}

	ShaderListID TitleScreen::GetShader()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/FullScreenAlphaTestedTexture.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId TitleScreen::GetTexture()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/title.bmp");

		static TextureId titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

		return titleScreenTextureID;
	}

	GeometryID TitleScreen::GetQuad()
	{
		static GeometryID titleScreenQuadID = SceneManager::GetInstance().GetGeometryManager()->CreateGeometry(Utilities::CreatePlaneGeometry(1.0f,1.0f));
		return titleScreenQuadID;
	}

	MaterialID TitleScreen::GetMaterial()
	{
		TextureParameter textureParameter(GetTexture());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GetShader());

		return titleScreenMaterialID;
	}

	void TitleScreen::CreateTitleScreenObject()
	{
		m_titleScreenObject = new Object(GetMaterial(), GetQuad(), Transform());
		AddObject(m_titleScreenObject);
			
		PerspectiveCameraParams params(45, 1280/720.0f, 0.1f, 1000.0f);
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

