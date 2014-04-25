#ifndef SCENEMANAGER_MATERIALPARAMETERS_H
#define SCENEMANAGER_MATERIALPARAMETERS_H

#include "GLM/include/glm/glm.hpp"
#include "Utilities/Color/Color.h"
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
	// THESE CLASSES HAVE THEIR MEMBER VARIABLES SET TO PUBLIC BECAUSE THEY ARE MEANT
	// TO BE USED LIKE STRUCTURES

	//-----------------------------------------------------------------------------
	class MaterialParameterBase
	{
	public:
		MaterialParameterBase(){}
		virtual ~MaterialParameterBase() = 0 {};	

		bool m_isActive;
	};

	//-----------------------------------------------------------------------------
	class PhongParameter : public MaterialParameterBase
	{
	public:
		PhongParameter()
		: m_ambiantColor(glm::vec4(1,1,1,1))
		, m_diffuseColor(glm::vec4(0,0,0,0))
		, m_specularColor(glm::vec4(0,0,0,0))
		, m_shininess(1)
		{
			m_isActive = false;
		}

		PhongParameter(const glm::vec4& ambiant, const glm::vec4& diffuse, const glm::vec4& specular, float shininess)
		: m_ambiantColor(ambiant)
		, m_diffuseColor(diffuse)
		, m_specularColor(specular)
		, m_shininess(shininess)
		{
			m_isActive = true;
		}

	public:
		glm::vec4 m_ambiantColor;
		glm::vec4 m_diffuseColor;
		glm::vec4 m_specularColor;
		float m_shininess;
	};

	//-----------------------------------------------------------------------------
	class PlainColorParameter : public MaterialParameterBase
	{
	public:
		PlainColorParameter()
		: m_color(glm::vec4(1,0,0,1))
		{
			m_isActive = false;			
		}

		PlainColorParameter(const glm::vec4& color)
		: m_color(color)
		{
			m_isActive = true;			
		}

	public:
		glm::vec4 m_color;
	};

	//-----------------------------------------------------------------------------
	class TextureParameter : public MaterialParameterBase
	{
	public: 
		TextureParameter()
		: m_textID(NULL)
		{
			m_isActive = false;
		}

		TextureParameter(TextureId textID)
		: m_textID(textID)
		{
			m_isActive = true;
		}

	public:
		TextureId m_textID;
	};

	//-----------------------------------------------------------------------------
	class ParallaxMapParameters : public MaterialParameterBase
	{
	public:
		ParallaxMapParameters()
		: m_parallaxmapID(0)
		, m_parallaxHeightScale(0.0f)
		, m_parallaxHeightBias(0.0f)
		{
			m_isActive = false;			
		}

		ParallaxMapParameters(TextureId texId, float heightScale, float heightBias)
		: m_parallaxmapID(texId)
		, m_parallaxHeightScale(heightScale)
		, m_parallaxHeightBias(heightBias)
		{
			m_isActive = true;
		}

	public:
		TextureId m_parallaxmapID;
		float m_parallaxHeightScale;
		float m_parallaxHeightBias;
	};
} // namespace SceneManager
} // namespace Atum


#endif
