#include "Light.h"
#include "LowLevelGraphics\Material\Shader\Shader.h"

namespace Atum
{
namespace SceneManager
{
	Light::Light()
	:m_baseLightParams()
	{}

	Light::Light(LightBaseParams params)
	:m_baseLightParams(params)
	{}

	Light::~Light()
	{}

	void Light::SetDiffuse(const glm::vec4& diffuse)
	{
		m_baseLightParams.diffuse = diffuse;
	}

	void Light::SetAmbient(const glm::vec4& ambient)
	{
		m_baseLightParams.ambient = ambient;
	}

	void Light::SetSpecular(const glm::vec4& specular)
	{
		m_baseLightParams.specular = specular;
	}
}
}