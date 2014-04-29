#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
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

			if(*state != GamePlayObject::WallStop && *state != GamePlayObject::Dead)
			{
				switch(IntersectMainCharacter(gameplayObject))
				{
				case IntersectionResult_Top:
					{
						if(*state != Jumping)
						{
							*state = GamePlayObject::Normal;
							return GetGameplayObjectType();
						}
						break;
					}
				case IntersectionResult_Left:
					{
						*state = GamePlayObject::WallStop;
						return GetGameplayObjectType();
					}
				case IntersectionResult_None:
					{
						if(*state != GamePlayObject::Jumping)
							*state = GamePlayObject::Falling;
						break;
					}
				}	
			}
		}
		return GamePlayObject::GamePlayObjectType_Invalid;
	}

	Platform::IntersectionResult Platform::IntersectMainCharacter(GamePlayObject* gameplayObject)
	{
		IntersectionResult result = IntersectMainCharacterWithPosition(gameplayObject->GetPosition(), gameplayObject->GetScale(), true);
		if(result == IntersectionResult_None)
		{
			result = IntersectMainCharacterWithPosition(gameplayObject->GetNextPosition(), gameplayObject->GetScale(), false);
			if(result == IntersectionResult_Top && gameplayObject->GetCharacterState() != Jumping) 
			{
				gameplayObject->SetXY(gameplayObject->GetPosition()[0],GetPosition()[1]+GetScale()[1]+0.15f);
			}
			else if(result == IntersectionResult_Left)
			{
				gameplayObject->SetXY(GetPosition()[0]-GetScale()[0]*0.5f-gameplayObject->GetScale()[0]*0.5f+0.15f, gameplayObject->GetPosition()[1]);
			}
		}
		else if(result == IntersectionResult_Top && gameplayObject->GetCharacterState() != Jumping)
		{
			gameplayObject->SetXY(gameplayObject->GetPosition()[0],GetPosition()[1]+GetScale()[1]+0.15f);
		}
		else if(result == IntersectionResult_Left)
		{
			gameplayObject->SetXY(GetPosition()[0]-GetScale()[0]*0.5f-gameplayObject->GetScale()[0]*0.5f+0.15f, gameplayObject->GetPosition()[1]);
		}

		return result;
	}

	Platform::IntersectionResult Platform::IntersectMainCharacterWithPosition(const glm::vec4& position, const glm::vec4& scale, bool upperBound)
	{
		float diffx = position[0]-GetPosition()[0];

		if(abs(diffx+(GetScale()[0]*0.5f+scale[0]*0.5f)) < 0.1f)
		{
			float diffy = position[1]-GetPosition()[1];
			if(diffy > -(GetScale()[1]*0.5f+scale[1]*0.5f) && diffy < GetScale()[1]*0.5f+scale[1]*0.5f)
			{	
				return IntersectionResult_Left;
			}
		}

		if(diffx > -(GetScale()[0]*0.5f+scale[0]*0.5f)+0.03f && diffx < GetScale()[0]*0.5f+scale[0]*0.5f)
		{			
			if(upperBound)
			{
				float diffy = (position[1]-scale[1]*0.5f)-(GetPosition()[1]+GetScale()[1]*0.5f);
				if(abs(diffy) < 0.15f)
					return IntersectionResult_Top;
			}
			else
			{
				float diffy = (position[1]-scale[1]*0.5f)-(GetPosition()[1]);
				if(abs(diffy) < 0.15f)
					return IntersectionResult_Top;
			}
		}

		return IntersectionResult_None;
	}

} // namespace SceneManager
} // namespace Atum
