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
		, m_currentSpriteState(Sprites_Above)
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

		UpdateSprite();
	}

	void MainCharacter::Reset()
	{
		m_speed = 0;
		SetXY(STARTING_X, STARTING_Y);
		SetScaleXY(0.5f*1.25f, 0.7993f*1.25f);
		m_cameraDiff = STARTING_Y;
		ms_cameraY = 0;

		m_currentSprite = GetTextureIDList()[Sprites_Above].begin();
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

		m_currentSpriteState = Sprites_Transition;
		m_currentSprite = GetTextureIDList()[Sprites_Transition].begin();

		m_currentState = GamePlayObject::Falling;
	}
	  
	void MainCharacter::BindShaderParameters()
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(GetShaderID()));
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("cameraY", &ms_cameraY, SHADER_FLOAT);

		LowLevelGraphics::ShaderProgram* shaderProgram = GetMaterial()->GetShaderList()->GetShaderProgram();
		LowLevelGraphics::Texture* diffuseMap = SceneManager::GetInstance().GetTextureManager()->GetTexture(*m_currentSprite);
		if(diffuseMap)
		{
			glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap->GetID());

			LowLevelGraphics::LowLevelAPI::ShaderProgramId shaderProgramId = GetMaterial()->GetShaderList()->GetShaderProgram()->GetProgramId();
			glUniform1i(LowLevelGraphics::LowLevelAPI::GetParameterLocation(shaderProgramId, DIFFUSEMAP_NAME), 0);
		} 
	}

	void MainCharacter::UpdateSprite()
	{
		if(m_currentState == GamePlayObject::Normal)
		{
			if(m_currentSpriteState == Sprites_Transition)
			{
				m_currentSprite = GetTextureIDList()[Sprites_Below].begin();
				m_currentSpriteState = Sprites_Below;
			}
			else
			{
				m_currentSprite++;
				if(m_currentSprite == GetTextureIDList()[m_currentSpriteState].end())
				{
					m_currentSprite = GetTextureIDList()[m_currentSpriteState].begin();
				}
			}
		} 

		else if(m_currentState == GamePlayObject::Falling || m_currentState == GamePlayObject::Jumping || m_currentState == GamePlayObject::WallStop)
		{
			if(m_currentSpriteState == Sprites_Transition)
			{
				static unsigned int frameCount = 0;  
				if(m_currentSprite != GetTextureIDList()[m_currentSpriteState].end()-1 && frameCount <= 8)
				{
					m_currentSprite++;
					frameCount++; 
				}
				else if(frameCount != 0)
				{
					frameCount--;
				}
			}
		} 
	}

	TextureId MainCharacter::GetTextureID()
	{
		return GetTextureIDList()[Sprites_Above][0];
	}

	std::vector<TextureId>* MainCharacter::GetTextureIDList()
	{
		if(m_textureIdListPerState[Sprites_Above].empty())
		{
			SceneManager& sceneManager = SceneManager::GetInstance();

			Utilities::Image::ImageParameters<unsigned char> titleScreenImage;

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0001.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0002.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0003.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0004.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0005.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0006.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0007.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0008.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0009.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0010.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Above_Running/cycleMarchePinguinStraight0011.png",true);
			m_textureIdListPerState[Sprites_Above].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0001.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0002.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0003.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0004.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0005.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0006.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0007.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0008.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0009.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0010.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0011.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0012.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0013.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0014.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0015.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0016.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0017.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Transition/transition0018.png");
			m_textureIdListPerState[Sprites_Transition].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0001.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0002.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0003.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0004.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0005.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0006.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0007.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0008.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0009.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0010.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));

			Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/textures/Sprites_Below_Running/cycleMarchePinguinStraight0011.png",true);
			m_textureIdListPerState[Sprites_Below].push_back(SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA));
		}

		return m_textureIdListPerState;
	}

} // namespace SceneManager
} // namespace Atum
