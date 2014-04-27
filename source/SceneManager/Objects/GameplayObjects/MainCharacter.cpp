#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
#include "SceneManager/SceneManager.h"

#define GRAVITY 0.0020f
#define MAX_FALLING_SPEED -1.2f
#define JUMPING_SPEED 0.08f

namespace Atum
{
namespace SceneManager
{
	MainCharacter::MainCharacter()
		: m_acceleration(GRAVITY)
        , m_speed(0)
		, m_currentState(GamePlayObject::Falling)
	{
		Events::EventManager::GetInstance().RegisterKeyboardListener(this);
		m_isPositionAffectedByLevel = false;
	}

	MainCharacter::~MainCharacter()
	{}

	void MainCharacter::GetPropertyList( PropertyList& o_properties )
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties

	}

	void MainCharacter::UpdatePropertyList( PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties
	}

	void MainCharacter::Init()
	{
		GamePlayObject::Init();

		SetXY(-4.0f, -0.2f);
		SetScaleXY(0.5f , 0.5f);
	}

	void MainCharacter::Uninit()
	{

	}

	void MainCharacter::Update()
	{
		GamePlayObject::Update();

		if(m_currentState == GamePlayObject::Jumping || m_currentState == GamePlayObject::Falling)
		{
			if(m_speed >= MAX_FALLING_SPEED)
				m_speed -= m_acceleration; 

			if(m_currentState == GamePlayObject::Jumping && m_speed < 0.0f)
			{
				m_currentState = GamePlayObject::Falling;
			}
		}
		else
		{
			m_speed = 0.0f;
		}

		SetRelativeXY(0.0f,m_speed);
	}

	void MainCharacter::Reset()
	{

	}

	TextureId MainCharacter::GetTextureID()
	{
		static TextureId textureID = INVALID_TEXTURE_ID;

		if (textureID == INVALID_TEXTURE_ID)
		{
			SceneManager& sceneManager = SceneManager::GetInstance();

			Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/MainCharacter.png");
			textureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);
		}

		return textureID;
	}

	MaterialID MainCharacter::GetMaterialID()
	{
		static MaterialID materialID = INVALID_MATERIAL_ID;

		if (materialID == INVALID_MATERIAL_ID)
		{
			TextureParameter textureParameter(GetTextureID());
			MaterialParameters materialParameters;
			materialParameters.diffuseMapParam = textureParameter;

			materialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GamePlayObject::GetShaderID());
		}

		return materialID;
	}

	GamePlayObject::GamePlayObjectType MainCharacter::Intersect(GamePlayObject* gameplayObject, GamePlayObject::CharacterState* state)
	{
		if(gameplayObject->GetGameplayObjectType() == GamePlayObject::GamePlayObjectType_MainCharacter)
			return GamePlayObject::GamePlayObjectType_Invalid;

		if(gameplayObject->Intersect(this, &m_currentState) != GamePlayObject::GamePlayObjectType_Invalid)
		{
			return gameplayObject->GetGameplayObjectType();
	    }

		return GamePlayObject::GamePlayObjectType_Invalid;
	}

	void MainCharacter::NotifyKeyPressed(const Events::KeyboardEvent& event)
	{
		if(event.GetEventType() == Events::KeyboardEventType::KEY_PRESSED)
		{
			if (event.GetKey() == ' ')
			{
				Jump();
			}
		}
	}

	void MainCharacter::Jump()
	{
		//if(m_currentState != GamePlayObject::Jumping &&
		//	m_currentState != GamePlayObject::Falling && 
		//	m_currentState != GamePlayObject::Dead)
		{
 			m_speed = JUMPING_SPEED;
			m_currentState = GamePlayObject::Jumping;
		}
	}

} // namespace SceneManager
} // namespace Atum
