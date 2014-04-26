#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
#include "SceneManager/SceneManager.h"

namespace Atum
{
namespace SceneManager
{
	MainCharacter::MainCharacter()
	{
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
	}

	void MainCharacter::Uninit()
	{

	}

	void MainCharacter::Update()
	{

	}

	void MainCharacter::Reset()
	{

	}

	TextureId MainCharacter::GetTexture()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/MainCharacter.png");
		static TextureId textureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

		return textureID;
	}

	MaterialID MainCharacter::GetMaterial()
	{
		TextureParameter textureParameter(GetTexture());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID materialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GamePlayObject::GetShader());

		return materialID;
	}

} // namespace SceneManager
} // namespace Atum
