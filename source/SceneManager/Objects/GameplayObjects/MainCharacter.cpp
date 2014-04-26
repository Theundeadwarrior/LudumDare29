#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
#include "SceneManager/SceneManager.h"

#define GRAVITY 0.0001f

namespace Atum
{
namespace SceneManager
{
	MainCharacter::MainCharacter()
		: m_acceleration(GRAVITY)
        , m_speed(0)
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

		SetXY(-0.4f, -0.2f);
		SetScaleXY(0.5f , 0.5f);
	}

	void MainCharacter::Uninit()
	{

	}

	void MainCharacter::Update()
	{
		GamePlayObject::Update();

		m_speed -= m_acceleration; 

		SetRelativeXY(0.0f,m_speed);
	}

	void MainCharacter::Reset()
	{

	}

	TextureId MainCharacter::GetTextureID()
	{
		static TextureId textureID = -1;

		if(textureID == -1)
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
		static MaterialID materialID = -1;

		if(materialID == -1)
		{
			TextureParameter textureParameter(GetTextureID());
			MaterialParameters materialParameters;
			materialParameters.diffuseMapParam = textureParameter;

			materialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GamePlayObject::GetShaderID());
		}

		return materialID;
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
		m_speed = 0.01f;
	}

} // namespace SceneManager
} // namespace Atum
