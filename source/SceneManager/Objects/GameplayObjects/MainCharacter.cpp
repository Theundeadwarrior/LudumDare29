#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
#include "SceneManager/SceneManager.h"

#define GRAVITY 0.015f
#define MAX_FALLING_SPEED -0.5f
#define JUMPING_SPEED 0.2f
#define STARTING_X -4.0f
#define STARTING_Y 2.2f
#define CAMERA_SOFT_THRESHOLD 1.0f
#define CAMERA_MOVEMENT 0.01f
#define CAMERA_STABILISATION 0.1f

namespace Atum
{
namespace SceneManager
{
	MainCharacter::MainCharacter()
		: m_speed(0)
		, m_currentState(GamePlayObject::Falling)
		, m_cameraDiff(STARTING_Y)
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

		Reset();
	}

	void MainCharacter::Uninit()
	{

	}

	void MainCharacter::Update()
	{
		if (m_currentState == GamePlayObject::Dead)
		{
			return;
		}

		GamePlayObject::Update();

		if(m_currentState == GamePlayObject::Jumping)
		{
			if(m_speed >= MAX_FALLING_SPEED)
				m_speed -= GRAVITY; 

			if(m_speed < 0.0f)
			{
				m_currentState = GamePlayObject::Falling;
			}
		}
		else if(m_currentState == GamePlayObject::Falling || m_currentState == GamePlayObject::WallStop)
		{
			if(m_speed >= 0.0f)
				m_speed = 0.0f;

			if(m_speed >= MAX_FALLING_SPEED)
				m_speed -= GRAVITY; 
		}
		else
		{
			m_speed = 0.0f;
		}

		SetRelativeXY(0.0f,m_speed);

		float diff = m_currentPosition.y - m_cameraDiff;
		if(diff > CAMERA_SOFT_THRESHOLD)
		{
			GamePlayObject::ms_cameraY -= CAMERA_MOVEMENT*abs(diff);
			m_cameraDiff += CAMERA_STABILISATION*abs(diff);
		}
		else if(diff < -CAMERA_SOFT_THRESHOLD)
		{
			GamePlayObject::ms_cameraY += CAMERA_MOVEMENT*abs(diff);
			m_cameraDiff -= CAMERA_STABILISATION*abs(diff);
		}
	}

	void MainCharacter::Reset()
	{
		m_speed = 0;
		SetXY(STARTING_X, STARTING_Y);
		SetScaleXY(0.5f*1.25f, 0.7993f*1.25f);
		m_cameraDiff = STARTING_Y;
		ms_cameraY = 0;
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

	void MainCharacter::GoBeneathTheSurface()
	{
		ms_cameraY = 0;
		m_speed = 0;
		m_cameraDiff = 20;
		m_currentPosition.y = -20;
	}

} // namespace SceneManager
} // namespace Atum
