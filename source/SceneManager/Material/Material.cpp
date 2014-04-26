#include "Material.h"
#include "Utilities/IdGenerator/IdGenerator.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Properties/PropertyList.h"
#include "SceneManager/Properties/Property.h"
#include "SceneManager/Properties/SelectionListProperty.h"
#include "SceneManager/Properties/TextureProperty.h"
#include "Utilities/Image/ImageUtilities.h"
#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"

namespace Atum
{
namespace SceneManager
{

//-----------------------------------------------------------------------------
// SHADERLIST METHODS
//-----------------------------------------------------------------------------
ShaderList::ShaderList( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::string args)
{
	m_shaderProgram = new LowLevelGraphics::ShaderProgram(vertexShaderFileName,fragmentShaderFileName, args);
}

//-----------------------------------------------------------------------------
ShaderList::~ShaderList()
{
	delete m_shaderProgram;
}

//-----------------------------------------------------------------------------
// MATERIAL METHODS
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Material::Material(ShaderListID shaderListId)
{
	m_shaderListID = shaderListId;
	InitDefaultParameters();
}

//-----------------------------------------------------------------------------
Material::Material(const MaterialParameters& materialParameters, ShaderListID shaderListId)
{
	m_shaderListID = shaderListId;
	m_materialParameters = materialParameters;

	// In case the user didn't set any active lighting technique
	//if(!m_materialParameters.phongParam.m_isActive)
	//{
	//	m_materialParameters.plainColorParam.m_isActive = true;
	//}
}

//-----------------------------------------------------------------------------
Material::~Material()
{
}

//-----------------------------------------------------------------------------
void Material::InitDefaultParameters()
{
	//ActivateEffect(NO_ILLUMINATION, &PlainColorParameter(glm::vec4(1,1,1,1)));
}

//-----------------------------------------------------------------------------
// Used to change shader according to the new parameters
//-----------------------------------------------------------------------------
void Material::UpdateShaderListID()
{
	std::bitset<MATERIALEFFECT_COUNT> effects;

	if(m_materialParameters.plainColorParam.m_isActive)
	{
		effects |= NO_ILLUMINATION;
	}
	else
	{
		effects |= PHONG_SHADING;
		if(m_materialParameters.parallaxParam.m_isActive)
		{
			effects |= PARALLAX_MAP;
		}
	}
	if(m_materialParameters.diffuseMapParam.m_isActive)
	{
		effects |= DIFFUSE_MAP;
	}

	ShaderListID id = SceneManager::GetInstance().GetShaderListManager()->GetShaderListIdFromFlags(effects);
	if(id != 0)
	{
		m_shaderListID = id;
	}
}

//-----------------------------------------------------------------------------
ShaderList* const Material::GetShaderList() const
{
	return SceneManager::GetInstance().GetShaderListManager()->GetShaderList(m_shaderListID);
}

//-----------------------------------------------------------------------------
LowLevelGraphics::Texture* const Material::GetDiffuseMap() const
{
    return SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.diffuseMapParam.m_textID);
}

//-----------------------------------------------------------------------------
LowLevelGraphics::Texture* const Material::GetParallaxMap() const
{
	return SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.parallaxParam.m_parallaxmapID);
}

//-----------------------------------------------------------------------------
void Material::BindShaderParameters()
{
	if(m_materialParameters.skyBoxParam.m_isActive)
	{
		BindSkyBoxToShader();
	}
	else
	{
		if(m_materialParameters.phongParam.m_isActive)
		{
			BindPhongToShader();
			if(m_materialParameters.parallaxParam.m_isActive)
			{
				BindParallaxToShader();
			}
		}
		else if(m_materialParameters.plainColorParam.m_isActive)
		{
			BindPlainColorToShader();
		}

		if(m_materialParameters.diffuseMapParam.m_isActive)
		{
			BindDiffuseMapToShader();
		}
	}
}

//-----------------------------------------------------------------------------
void Material::UnbindShaderParameters()
{
	LowLevelGraphics::LowLevelAPI::ShaderParameterId shaderParameter;
	if(m_materialParameters.skyBoxParam.m_isActive)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,NULL);
	}
	else
	{
		if(m_materialParameters.diffuseMapParam.m_isActive)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,NULL);
			//shaderParameter = LowLevelGraphics::LowLevelAPI::GetParameterLocation(GetShaderList()->GetShaderProgram()->GetProgramId(),TEXTURE_NAME);
			//LowLevelGraphics::LowLevelAPI::DisableTextureShaderParameter(shaderParameter);
		}
		if(m_materialParameters.parallaxParam.m_isActive)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D,NULL);
			//shaderParameter = LowLevelGraphics::LowLevelAPI::GetParameterLocation(GetShaderList()->GetShaderProgram()->GetProgramId(),PARALLAXMAP_NAME);
			//LowLevelGraphics::LowLevelAPI::DisableTextureShaderParameter(shaderParameter);
		}
	}
}

//-----------------------------------------------------------------------------
void Material::BindDiffuseMapToShader()
{
	LowLevelGraphics::ShaderProgram* shaderProgram = GetShaderList()->GetShaderProgram();
	LowLevelGraphics::Texture* diffuseMap = GetDiffuseMap();
	if(diffuseMap)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap->GetID());

		LowLevelGraphics::LowLevelAPI::ShaderProgramId shaderProgramId = GetShaderList()->GetShaderProgram()->GetProgramId();
		glUniform1i(LowLevelGraphics::LowLevelAPI::GetParameterLocation(shaderProgramId, DIFFUSEMAP_NAME), 0);
	}
}

//-----------------------------------------------------------------------------
void Material::BindSkyBoxToShader()
{
	LowLevelGraphics::ShaderProgram* shaderProgram = GetShaderList()->GetShaderProgram();
	LowLevelGraphics::TextureSkyBox* textureSkyBox = GetSkyBox();
	if(textureSkyBox)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureSkyBox->GetID());

		LowLevelGraphics::LowLevelAPI::ShaderProgramId shaderProgram = GetShaderList()->GetShaderProgram()->GetProgramId();
		glUniform1i(LowLevelGraphics::LowLevelAPI::GetParameterLocation(shaderProgram, "SkyBox"), 0);
	}
}

//-----------------------------------------------------------------------------
void Material::BindParallaxToShader()
{
	LowLevelGraphics::LowLevelAPI::ShaderParameterId shaderParameter;
	LowLevelGraphics::ShaderProgram* shaderProgram = GetShaderList()->GetShaderProgram();
	LowLevelGraphics::Texture* parallaxMap = GetParallaxMap();

	if(parallaxMap)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, parallaxMap->GetID());

		LowLevelGraphics::LowLevelAPI::ShaderProgramId shaderProgramId = GetShaderList()->GetShaderProgram()->GetProgramId();
		glUniform1i(LowLevelGraphics::LowLevelAPI::GetParameterLocation(shaderProgramId, PARALLAXMAP_NAME), 1);

		shaderProgram->UpdateShaderParameter(LowLevelGraphics::PARALLAXHEIGHTSCALE, &m_materialParameters.parallaxParam.m_parallaxHeightScale,SHADER_FLOAT);
		shaderProgram->UpdateShaderParameter(LowLevelGraphics::PARALLAXHEIGHTBIAS, &m_materialParameters.parallaxParam.m_parallaxHeightBias,SHADER_FLOAT);
	}
}

//-----------------------------------------------------------------------------
void Material::BindPhongToShader()
{
	LowLevelGraphics::ShaderProgram* shaderProgram = GetShaderList()->GetShaderProgram();
	shaderProgram->UpdateShaderParameterWithName("MaterialDiffuse", &m_materialParameters.phongParam.m_diffuseColor, SHADER_FLOAT4);	
	shaderProgram->UpdateShaderParameterWithName("MaterialSpecular", &m_materialParameters.phongParam.m_specularColor, SHADER_FLOAT4);	
	shaderProgram->UpdateShaderParameterWithName("MaterialAmbient", &m_materialParameters.phongParam.m_ambiantColor, SHADER_FLOAT4);	
	shaderProgram->UpdateShaderParameterWithName("MaterialShininess", &m_materialParameters.phongParam.m_shininess, SHADER_FLOAT);	
}

//-----------------------------------------------------------------------------
void Material::BindPlainColorToShader()
{
	LowLevelGraphics::ShaderProgram* shaderProgram = GetShaderList()->GetShaderProgram();
	shaderProgram->UpdateShaderParameterWithName("PlainColor", &m_materialParameters.plainColorParam.m_color, SHADER_FLOAT4);	
}

//-----------------------------------------------------------------------------
void Material::ActivateEffect( MaterialEffectsFlags effect, MaterialParameterBase* parameter )
{
	switch(effect)
	{
	case NO_ILLUMINATION:
		{
			PlainColorParameter* param = dynamic_cast<PlainColorParameter*>(parameter);
			if(param)
			{
				m_materialParameters.plainColorParam = *param;
				m_materialParameters.plainColorParam.m_isActive = true;
				m_materialParameters.phongParam.m_isActive = false;
			}
			break;
		}
	case PHONG_SHADING:
		{
			PhongParameter* param = dynamic_cast<PhongParameter*>(parameter);
			if(param)
			{
				m_materialParameters.phongParam = *param;
				m_materialParameters.phongParam.m_isActive = true;
				m_materialParameters.plainColorParam.m_isActive = false;
			}
			break;
		}
	case DIFFUSE_MAP:
		{
			TextureParameter* param = dynamic_cast<TextureParameter*>(parameter);
			if(param)
			{
				m_materialParameters.diffuseMapParam = *param;
				m_materialParameters.diffuseMapParam.m_isActive = true;
			}
			break;
		}
	case PARALLAX_MAP:
		{
			ParallaxMapParameters* param = dynamic_cast<ParallaxMapParameters*>(parameter);
			if(param)
			{
				m_materialParameters.parallaxParam = *param;
				m_materialParameters.parallaxParam.m_isActive = true;
			}
			break;
		}
	default:
		ATUM_ASSERT_MESSAGE(false, "Parameter Type doesn't exist.");
	}
	
	UpdateShaderListID();
}

//-----------------------------------------------------------------------------
void Material::DeactivateEffect( MaterialEffectsFlags effect )
{
	switch(effect)
	{
		case DIFFUSE_MAP:
			{
				m_materialParameters.diffuseMapParam.m_isActive = false;
				break;
			}
		case PARALLAX_MAP:
			{
				m_materialParameters.parallaxParam.m_isActive = false;
				break;
			}
		default:
			ATUM_ASSERT_MESSAGE(false, "Parameter Type doesn't exist.");
	}
	UpdateShaderListID();
}

LowLevelGraphics::TextureSkyBox* const Material::GetSkyBox() const
{
	return SceneManager::GetInstance().GetTextureManager()->GetSkyBox(m_materialParameters.skyBoxParam.m_textID);
}

//-----------------------------------------------------------------------------
void Material::GetLightingPropertyList( PropertyList& o_properties )
{
	if(m_materialParameters.phongParam.m_isActive)
	{
		Property* lightTech = new SelectionListProperty(
			"LightingTechnique", SceneManager::GetInstance().GetMaterialManager()->GetLightingTechniques(), 1);
		o_properties.AddProperty(lightTech);

		Property* ambiant = new Property("Ambiant", glm::vec3(m_materialParameters.phongParam.m_ambiantColor), VECTORTYPE_COLOR);
		Property* diffuse = new Property("Diffuse", glm::vec3(m_materialParameters.phongParam.m_diffuseColor), VECTORTYPE_COLOR);
		Property* specular = new Property("Specular", glm::vec3(m_materialParameters.phongParam.m_specularColor), VECTORTYPE_COLOR);
		Property* shininess = new Property("Shininess", m_materialParameters.phongParam.m_shininess);
		o_properties.AddProperty(ambiant);
		o_properties.AddProperty(diffuse);
		o_properties.AddProperty(specular);
		o_properties.AddProperty(shininess);
	}
	else if(m_materialParameters.plainColorParam.m_isActive)
	{
		Property* lightTech = new SelectionListProperty(
			"LightingTechnique", SceneManager::GetInstance().GetMaterialManager()->GetLightingTechniques(), 0);
		o_properties.AddProperty(lightTech);

		Property* plainColor = new Property("Color", glm::vec3(m_materialParameters.plainColorParam.m_color), VECTORTYPE_COLOR);
		o_properties.AddProperty(plainColor);
	}
}

//-----------------------------------------------------------------------------
void Material::UpdateLightingPropertyList( PropertyList& properties )
{
	const Property* lightTech = properties.GetProperty("LightingTechnique");
	int lightId;
	lightTech->GetValue(lightId);
	if(lightId == 1)
	{
		if(!m_materialParameters.phongParam.m_isActive)
		{
			// We are changing shader type
			m_materialParameters.phongParam.m_isActive = true;
			m_materialParameters.plainColorParam.m_isActive = false;
			UpdateShaderListID();
		}
		else
		{
			const Property* ambiant = properties.GetProperty("Ambiant");
			glm::vec3 ambiantValue;
			ambiant->GetValue(ambiantValue);
			m_materialParameters.phongParam.m_ambiantColor = glm::vec4(ambiantValue,1);

			const Property* diffuse = properties.GetProperty("Diffuse");
			glm::vec3 diffuseValue;
			diffuse->GetValue(diffuseValue);
			m_materialParameters.phongParam.m_diffuseColor = glm::vec4(diffuseValue,1);

			const Property* specular = properties.GetProperty("Specular");
			glm::vec3 specularValue;
			specular->GetValue(specularValue);
			m_materialParameters.phongParam.m_specularColor = glm::vec4(specularValue,1);

			const Property* shininess = properties.GetProperty("Shininess");
			shininess->GetValue(m_materialParameters.phongParam.m_shininess);
		}
	}
	else if(lightId == 0)
	{
		if(!m_materialParameters.plainColorParam.m_isActive)
		{
			// We are changing shader type
			m_materialParameters.phongParam.m_isActive = false;
			m_materialParameters.plainColorParam.m_isActive = true;
			UpdateShaderListID();
		}
		else
		{
			const Property* color = properties.GetProperty("Color");
			glm::vec3 colorValue;
			color->GetValue(colorValue);
			m_materialParameters.plainColorParam.m_color = glm::vec4(colorValue,1);
		}
	}
}

//-----------------------------------------------------------------------------
void Material::GetEffectPropertyList( PropertyList& o_properties )
{
	LowLevelGraphics::Texture* diffuseMapTexture = SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.diffuseMapParam.m_textID);
	std::string currentDiffuseTexPath("");
	if(diffuseMapTexture && m_materialParameters.diffuseMapParam.m_isActive )
	{
		currentDiffuseTexPath = diffuseMapTexture->GetPath();
	}
	Property* diffuseMap = new TextureProperty("DiffuseMap", currentDiffuseTexPath);
	o_properties.AddProperty(diffuseMap);

	LowLevelGraphics::Texture* parallaxMapTexture = SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.parallaxParam.m_parallaxmapID);
	std::string currentParallaxTexPath("");
	if(parallaxMapTexture && m_materialParameters.parallaxParam.m_isActive )
	{
		currentParallaxTexPath = parallaxMapTexture->GetPath();
		Property* parallaxHeightScale = new Property("Parallax Height Scale", m_materialParameters.parallaxParam.m_parallaxHeightScale);
		Property* parallaxHeightBias = new Property("Parallax Height Bias", m_materialParameters.parallaxParam.m_parallaxHeightBias);
		o_properties.AddProperty(parallaxHeightScale);
		o_properties.AddProperty(parallaxHeightBias);
	}
	Property* parallaxMap = new TextureProperty("ParallaxMap", currentParallaxTexPath);
	o_properties.AddProperty(parallaxMap);

}

//-----------------------------------------------------------------------------
void Material::UpdateEffectPropertyList( PropertyList& properties )
{
	const Property* diffuseMap = properties.GetProperty("DiffuseMap");
	std::string newDiffuseMapPath;
	diffuseMap->GetValue(newDiffuseMapPath);

	LowLevelGraphics::Texture* diffuseMapTexture = SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.diffuseMapParam.m_textID);
	if ( newDiffuseMapPath.size() == 0 )
	{
		m_materialParameters.diffuseMapParam.m_isActive = false;
		UpdateShaderListID();
	}
	else if ( !diffuseMapTexture|| newDiffuseMapPath.compare(diffuseMapTexture->GetPath()))
	{
		m_materialParameters.diffuseMapParam.m_isActive = true;
		Utilities::Image::ImageParameters<unsigned char> imageParameter;
		Utilities::Image::LoadImageFromFile(imageParameter, newDiffuseMapPath.c_str());
		unsigned int texId = SceneManager::GetInstance().GetTextureManager()->CreateTexture(imageParameter, LowLevelGraphics::LowLevelAPI::ATUM_RGB);
		m_materialParameters.diffuseMapParam.m_textID = texId;
		UpdateShaderListID();
	}
	else if ( newDiffuseMapPath.compare(diffuseMapTexture->GetPath()) == 0 )
	{
		m_materialParameters.diffuseMapParam.m_isActive = true;
	}

	const Property* parallaxMap = properties.GetProperty("ParallaxMap");
	std::string newParallaxMapPath;
	parallaxMap->GetValue(newParallaxMapPath);

	LowLevelGraphics::Texture* parallaxMapTexture = SceneManager::GetInstance().GetTextureManager()->GetTexture(m_materialParameters.parallaxParam.m_parallaxmapID);
	if( newParallaxMapPath.size() == 0)
	{
		m_materialParameters.parallaxParam.m_isActive = false;
		UpdateShaderListID();
	}
	else if( !parallaxMapTexture || newParallaxMapPath.compare(parallaxMapTexture->GetPath()))
	{
		m_materialParameters.parallaxParam.m_isActive = true;
		Utilities::Image::ImageParameters<unsigned char> imageParameter;
		Utilities::Image::LoadImageFromFile(imageParameter, newParallaxMapPath.c_str());
		unsigned int texId = SceneManager::GetInstance().GetTextureManager()->CreateTexture(imageParameter, LowLevelGraphics::LowLevelAPI::ATUM_RGBA);
		m_materialParameters.parallaxParam.m_parallaxmapID = texId;

		UpdateShaderListID();
	}
	else if ( newParallaxMapPath.compare(parallaxMapTexture->GetPath()) == 0 )
	{
		m_materialParameters.parallaxParam.m_isActive = true;
	}

	const Property* parallaxHeightScale = properties.GetProperty("Parallax Height Scale");
	if ( parallaxHeightScale )
		parallaxHeightScale->GetValue(m_materialParameters.parallaxParam.m_parallaxHeightScale);

	const Property* parallaxHeightBias = properties.GetProperty("Parallax Height Bias");
	if ( parallaxHeightBias )
		parallaxHeightBias->GetValue(m_materialParameters.parallaxParam.m_parallaxHeightBias);

	UpdateShaderListID();
}

}
}

