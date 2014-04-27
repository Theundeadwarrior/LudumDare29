#include "SceneManager/Objects/GameplayObjects/PlatformBridge.h"
#include "SceneManager/SceneManager.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Level/Level.h"

namespace Atum
{
namespace SceneManager
{
	PlatformBridge::PlatformBridge(glm::vec4 position, glm::vec4 scale)
		: Platform(position, scale)
	{
	}

	//const GamePlayObject::GamePlayObjectType PlatformCanyon::GetGameplayObjectType() const
	//{
	//	throw std::exception("The method or operation is not implemented.");
	//}


	TextureId PlatformBridge::GetTextureID()
	{
		static TextureId textureID = INVALID_TEXTURE_ID;

		SceneManager& sceneManager = SceneManager::GetInstance();

		if (textureID == INVALID_TEXTURE_ID)
		{
			Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Platform.png");
			textureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);
		}

		return textureID;
	}

	MaterialID PlatformBridge::GetMaterialID()
	{
		static MaterialID materialID = INVALID_MATERIAL_ID;

		if (materialID == INVALID_MATERIAL_ID)
		{
			TextureParameter textureParameter(GetTextureID());
			MaterialParameters materialParameters;
			materialParameters.diffuseMapParam = textureParameter;
			materialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters, GamePlayObject::GetShaderID());
		}
		
		return materialID;
	}

	void PlatformBridge::Init()
	{
		Platform::Init();
		/*GamePlayObject::Init();
		SetXY(m_currentPosition.x, m_currentPosition.y);
		SetScaleXY(m_scale.x, m_scale.y);
		*///throw std::exception("The method or operation is not implemented.");
	}

	void PlatformBridge::Uninit()
	{
		throw std::exception("The method or operation is not implemented.");
	}

} // namespace SceneManager
} // namespace Atum
