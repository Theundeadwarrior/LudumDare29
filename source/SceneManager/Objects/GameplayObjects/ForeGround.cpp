#include "SceneManager/Objects/GameplayObjects/ForeGround.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


namespace Atum
{
namespace SceneManager 
{
	Foreground::Foreground()
		:m_uOffset(0.0f)
	{
		SetScaleXY(2.2f,1.3f);
		SetXY(0.f,-0.8f); 
		m_isPositionAffectedByLevel = false;
	}

	Foreground::~Foreground()
	{
	}

	void Foreground::BindShaderParameters()
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(GetShaderID()));
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);

		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("uOffset", &m_uOffset, SHADER_FLOAT);

		GetMaterial()->BindDiffuseMapToShader();
	}

	ShaderListID Foreground::GetShaderID()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/BackGroundObject.vx", "../../data/shaders/ForeGroundObject.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId Foreground::GetTextureID()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/foreground_desert.png");

		static TextureId titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

		return titleScreenTextureID;
	}

	MaterialID Foreground::GetMaterialID()
	{
		TextureParameter textureParameter(GetTextureID());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GetShaderID());

		return titleScreenMaterialID;
	}

	void Foreground::Move()
	{
		m_uOffset += 0.005f;

		if(m_uOffset > 1.0f)
		{
			m_uOffset = 0.0f;
		}
	}

} // namespace SceneManager
} // namespace Atum

