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
		SetScaleXY(2.2f,2.2f);
		SetXY(0.f,-0.4f); 
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

		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("cameraY", &GamePlayObject::ms_cameraY, SHADER_FLOAT);

		GetMaterial()->BindDiffuseMapToShader();
	}

	ShaderListID Foreground::GetShaderID()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/ForeGroundObject.vx", "../../data/shaders/ForeGroundObject.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId Foreground::GetTextureID()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> foreGroundIceTexture;
		Utilities::Image::LoadImageFromFile(foreGroundIceTexture, "../../data/placeholders/foreground_desert.png");

		static TextureId foreGroundIceTextureId = SceneManager::GetInstance().GetTextureManager()->CreateTexture(foreGroundIceTexture, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

		return foreGroundIceTextureId;
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
		if(m_uOffset >= 2.0f)
		{
			m_uOffset = 0.0f;
		}

		m_uOffset += 0.015f;
	}

} // namespace SceneManager
} // namespace Atum

