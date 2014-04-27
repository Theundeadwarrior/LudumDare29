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
		:m_uOffset(0.0f)
	{
		SetScaleXY(4.f,4.f);
		SetXY(0.f,0.3f); 
		m_isPositionAffectedByLevel = false;
	}

	Background::~Background()
	{
	}

	void Background::BindShaderParameters()
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(GetShaderID()));
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);

		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("uOffset", &m_uOffset, SHADER_FLOAT);

		GetMaterial()->BindDiffuseMapToShader();
	}

	ShaderListID Background::GetShaderID()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/BackGroundObject.vx", "../../data/shaders/BackGroundObject.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId Background::GetTextureID()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/desertbackground.bmp");

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

	void Background::Move()
	{
		m_uOffset += 0.0001f;

		if(m_uOffset > 1.0f)
		{
			m_uOffset = 0.0f;
		}
	}

} // namespace SceneManager
} // namespace Atum

