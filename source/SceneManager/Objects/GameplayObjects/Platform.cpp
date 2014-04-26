#include "SceneManager/Objects/GameplayObjects/Platform.h"
#include "SceneManager/SceneManager.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Level/Level.h"

namespace Atum
{
namespace SceneManager
{
	Platform::Platform(glm::vec4 position, glm::vec4 scale)
		: GamePlayObject(position, scale)
	{
	}

	const GamePlayObject::GamePlayObjectType Platform::GetGameplayObjectType() const
	{
		return GamePlayObjectType_Platform;
	}


	TextureId Platform::GetTextureID()
	{
		//static TextureId textureID = INVALID_TEXTURE_ID;

		//SceneManager& sceneManager = SceneManager::GetInstance();

		//if (textureID == INVALID_TEXTURE_ID)
		//{
		//	Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		//	Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Platform.png");
		//	textureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGB);
		//}

		//return textureID;
		return INVALID_TEXTURE_ID;
	}

	MaterialID Platform::GetMaterialID()
	{
		//static MaterialID materialID = INVALID_MATERIAL_ID;

		//if (materialID == INVALID_MATERIAL_ID)
		//{
		//	TextureParameter textureParameter(GetTextureID());
		//	MaterialParameters materialParameters;
		//	materialParameters.diffuseMapParam = textureParameter;
		//	materialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters, GamePlayObject::GetShaderID());
		//}
		//
		//return materialID;
		return INVALID_MATERIAL_ID;
	}

	void Platform::Init()
	{
		GamePlayObject::Init();
		SetXY(m_currentPosition.x, m_currentPosition.y);
		SetScaleXY(m_scale.x, m_scale.y);
		//throw std::exception("The method or operation is not implemented.");
	}

	void Platform::Uninit()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	GamePlayObject::GamePlayObjectType Platform::Intersect(GamePlayObject* gameplayObject, GamePlayObject::CharacterState* state)
	{
		switch(gameplayObject->GetGameplayObjectType())
		{
		case GamePlayObject::GamePlayObjectType_MainCharacter:

		default:
			return GamePlayObject::GamePlayObjectType_Invalid;
		}
	}

} // namespace SceneManager
} // namespace Atum
