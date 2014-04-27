#include "SceneManager/Objects/GameplayObjects/Background.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


namespace Atum
{
namespace SceneManager
{
	Background::Background()
	{
	}

	Background::~Background()
	{
	}

	ShaderListID Background::GetShaderID()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/FullScreenAlphaTestedTexture.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId Background::GetTextureID()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/TitleScreen.bmp");

		static TextureId titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);

		return titleScreenTextureID;
	}

	MaterialID Background::GetMaterialID()
	{
		TextureParameter textureParameter(GetTextureID());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GetShaderID());

		return titleScreenMaterialID;
	}

} // namespace SceneManager
} // namespace Atum

