#include "SceneManager/Objects/GameplayObjects/MovingBackground.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"

#include "Utilities/Image/ImageUtilities.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


namespace Atum
{
namespace SceneManager
{
	MovingBackground::MovingBackground()
		:m_uOffset(0.0f)
	{
		SetScaleXY(4.f,4.f);
		SetXY(0.f,0.3f); 
		m_isPositionAffectedByLevel = false;
	}

	MovingBackground::~MovingBackground()
	{
	}

	void MovingBackground::BindShaderParameters()
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(GetShaderID()));
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);

		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("uOffset", &m_uOffset, SHADER_FLOAT);

		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("cameraY", &GamePlayObject::ms_cameraY, SHADER_FLOAT);

		GetMaterial()->BindDiffuseMapToShader();
	}

	ShaderListID MovingBackground::GetShaderID()
	{
		static ShaderListID alphaTexturedQuadShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/MovingBackGroundObject.vx", "../../data/shaders/MovingBackGroundObject.fg", NULL);
		return alphaTexturedQuadShaderID;
	}

	TextureId MovingBackground::GetTextureID()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();

		Utilities::Image::ImageParameters<unsigned char> titleScreenImage;
		Utilities::Image::LoadImageFromFile(titleScreenImage, "../../data/placeholders/glace.png");

		static TextureId titleScreenTextureID = SceneManager::GetInstance().GetTextureManager()->CreateTexture(titleScreenImage, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);

		return titleScreenTextureID;
	}

	MaterialID MovingBackground::GetMaterialID()
	{
		TextureParameter textureParameter(GetTextureID());
		MaterialParameters materialParameters;
		materialParameters.diffuseMapParam = textureParameter;

		static MaterialID titleScreenMaterialID = SceneManager::GetInstance().GetMaterialManager()->CreateMaterial(materialParameters,GetShaderID());

		return titleScreenMaterialID;
	}

	void MovingBackground::Move()
	{
		if(m_uOffset >= 2.0f)
		{
			m_uOffset = 0.0f;
		}

		m_uOffset += 0.00016f;
	}

} // namespace SceneManager
} // namespace Atum

