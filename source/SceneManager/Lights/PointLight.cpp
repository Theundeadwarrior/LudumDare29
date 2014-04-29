#include "PointLight.h"
#include "LowLevelGraphics\Material\Shader\ShaderProgram.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Properties/Property.h"
#include "SceneManager/Properties/PropertyList.h"

namespace Atum
{
namespace SceneManager
{

PointLight::PointLight()
:Light()
,m_radius(5.0f)
,m_transform()
{

}

PointLight::PointLight(const LightBaseParams& baseParams,const Transform& transform, float radius)
	:Light(baseParams)
	,m_radius(radius)
	,m_transform(transform)
{
	UpdateAABB();
}

PointLight::~PointLight()
{

}

void PointLight::SetDiffuse(const glm::vec4& diffuse)
{
	Light::SetDiffuse(diffuse);
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSDIFFUSE, m_index, &m_baseLightParams.diffuse, SHADER_LIGHT_DIFFUSE);
}

void PointLight::SetAmbient(const glm::vec4& ambient)
{
	Light::SetAmbient(ambient);
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSAMBIENT, m_index, &m_baseLightParams.ambient, SHADER_LIGHT_AMBIENT);
}

void PointLight::SetSpecular(const glm::vec4& specular)
{
	Light::SetSpecular(specular);
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSSPECULAR, m_index, &m_baseLightParams.specular, SHADER_LIGHT_SPECULAR);
}

void PointLight::SetTransform(const Transform& transform)
{
	m_transform = transform;
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSTRANSFORM, m_index, &m_transform.GetMatrix(), SHADER_LIGHT_TRANSFORM);
}

void PointLight::SetRadius(float radius)
{
	m_radius = radius;
	//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSRADIUS, m_index, &m_radius, SHADER_LIGHT_RADIUS);
}

void PointLight::UpdateAABB()
{
	glm::vec3 position(m_transform.GetPosition());
	m_aabb.m_maxBounds = (position += 0.5);
	m_aabb.m_minBounds = (position -= 1);
}

void PointLight::GetPropertyList( PropertyList& o_properties ) const
{
	Property* name = new Property( COMP_PROP_NAME, GetName() );
	o_properties.AddProperty(name);

	Property* position = new Property( COMP_PROP_POSITION, m_transform.GetPosition() );
	o_properties.AddProperty(position);
}

void PointLight::UpdatePropertyList( const PropertyList& i_properties )
{
	const Property* name = i_properties.GetProperty(COMP_PROP_NAME);
	if ( name )
	{
		name->GetValue(m_name);
	}
	const Property* position = i_properties.GetProperty(COMP_PROP_POSITION);
	if ( position )
	{
		glm::vec3 newPos;
		position->GetValue(newPos);
		m_transform.SetTranslate(newPos);
		Update();
	}
}

void PointLight::Update()
{
	m_transform.UpdateMatrices();
	SceneManager::GetInstance().GetCurrentScene()->UpdateAllPointLights();
	UpdateAABB();
}

}
}