#ifndef SCENEMANAGER_CUBE_CPP
#define SCENEMANAGER_CUBE_CPP

#include "PointCloud.h"
#include "Events/EventManager.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Scene/Scene.h"
#include <GLM/include/glm/gtc/type_ptr.hpp>
#include "SceneManager/Properties/Property.h"
#include "SceneManager/Properties/PropertyList.h"
#include <string>

namespace Atum
{
namespace SceneManager
{
	PointCloud::PointCloud(MaterialID materialID, GeometryID geomId, const Transform & transform, const Utilities::AABB & aabb)
		:Object(materialID, geomId, transform, aabb)
	{
		m_xMin = m_aabb.m_minBounds.x;
		m_xMax = m_aabb.m_maxBounds.x;
		m_yMin = m_aabb.m_minBounds.y;
		m_yMax = m_aabb.m_maxBounds.y;
		m_zMin = m_aabb.m_minBounds.z;
		m_zMax = m_aabb.m_maxBounds.z;
		m_distanceShellSphere = 3.0f;
		m_distanceViewPlane = 2.0f;
		m_selectedAxe = XAXE_SELECTED;
		m_name = "Cloud of points";

		// generate parameters for the property list
		char value[100];
		sprintf(value, "%f", m_aabb.m_minBounds.x);
		m_parametersXMin += " Min=";
		m_parametersXMin += value;
		m_parametersXMax += " Min=";
		m_parametersXMax += value;

		sprintf(value, "%f", m_aabb.m_maxBounds.x);
		m_parametersXMin += " Max=";
		m_parametersXMin += value;
		m_parametersXMax += " Max=";
		m_parametersXMax += value;

		sprintf(value, "%f", m_aabb.m_minBounds.y);
		m_parametersYMin += " Min=";
		m_parametersYMin += value;
		m_parametersYMax += " Min=";
		m_parametersYMax += value;

		sprintf(value, "%f", m_aabb.m_maxBounds.y);
		m_parametersYMin += " Max=";
		m_parametersYMin += value;
		m_parametersYMax += " Max=";
		m_parametersYMax += value;

		sprintf(value, "%f", m_aabb.m_minBounds.z);
		m_parametersZMin += " Min=";
		m_parametersZMin += value;
		m_parametersZMax += " Min=";
		m_parametersZMax += value;

		sprintf(value, "%f", m_aabb.m_maxBounds.z);
		m_parametersZMin += " Max=";
		m_parametersZMin += value;
		m_parametersZMax += " Max=";
		m_parametersZMax += value;

		m_parametersDistanceViewPlane += " Min=0.0";
		m_parametersDistanceShellSphere += " Min=0.0";

		std::string stepFloat = " Step=0.01";
		m_parametersXMin += stepFloat;
		m_parametersXMax += stepFloat;
		m_parametersYMin += stepFloat;
		m_parametersYMax += stepFloat;
		m_parametersZMin += stepFloat;
		m_parametersZMax += stepFloat;
		m_parametersDistanceViewPlane += stepFloat;
		m_parametersDistanceShellSphere += stepFloat;

		Events::EventManager::GetInstance().RegisterKeyboardListener(this);
		Events::EventManager::GetInstance().RegisterMouseListener(this);
	}

	PointCloud::~PointCloud()
	{
		Events::EventManager::GetInstance().UnregisterMouseListener(this);
		Events::EventManager::GetInstance().UnregisterKeyboardListener(this);
	}

	void PointCloud::GetPropertyList( PropertyList& o_properties ) const
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties
		
		Property* property = new Property(POINTCLOUD_XMIN_NAME, m_xMin, m_parametersXMin);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_XMAX_NAME, m_xMax, m_parametersXMax);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_YMIN_NAME, m_yMin, m_parametersYMin);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_YMAX_NAME, m_yMax, m_parametersYMax);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_ZMIN_NAME, m_zMin, m_parametersZMin);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_ZMAX_NAME, m_zMax, m_parametersZMax);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_DISTANCEVIEWPLANE_NAME, m_distanceViewPlane, m_parametersDistanceViewPlane);
		o_properties.AddProperty(property);

		property = new Property(POINTCLOUD_DISTANCESHELLSPHERE_NAME, m_distanceShellSphere, m_parametersDistanceShellSphere);
		o_properties.AddProperty(property);
	}

	void PointCloud::UpdatePropertyList(const PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties

		// Binds the correct shader before updating :
		LowLevelGraphics::LowLevelAPI::BindShaders(GetMaterial()->GetShaderList());

		const Property* xMin = i_properties.GetProperty(POINTCLOUD_XMIN_NAME);
		if (xMin)
		{
			xMin->GetValue(m_xMin);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMin", &m_xMin, SHADER_FLOAT);
		}
		const Property* xMax = i_properties.GetProperty(POINTCLOUD_XMAX_NAME);
		if (xMax)
		{
			xMax->GetValue(m_xMax);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMax", &m_xMax, SHADER_FLOAT);
		}
		const Property* yMin = i_properties.GetProperty(POINTCLOUD_YMIN_NAME);
		if (yMin)
		{
			yMin->GetValue(m_yMin);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMin", &m_yMin, SHADER_FLOAT);
		}
		const Property* yMax = i_properties.GetProperty(POINTCLOUD_YMAX_NAME);
		if (yMax)
		{
			yMax->GetValue(m_yMax);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMax", &m_yMax, SHADER_FLOAT);
		}
		const Property* zMin = i_properties.GetProperty(POINTCLOUD_ZMIN_NAME);
		if (zMin)
		{
			zMin->GetValue(m_zMin);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMin", &m_zMin, SHADER_FLOAT);
		}
		const Property* zMax = i_properties.GetProperty(POINTCLOUD_ZMAX_NAME);
		if (zMax)
		{
			zMax->GetValue(m_zMax);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMax", &m_zMax, SHADER_FLOAT);
		}

		const Property* distanceViewPlane = i_properties.GetProperty(POINTCLOUD_DISTANCEVIEWPLANE_NAME);
		if (distanceViewPlane)
		{
			distanceViewPlane->GetValue(m_distanceViewPlane);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("distanceViewPlane", &m_distanceViewPlane, SHADER_FLOAT);
		}

		const Property* contraction = i_properties.GetProperty(POINTCLOUD_DISTANCESHELLSPHERE_NAME);
		if (contraction)
		{
			contraction->GetValue(m_distanceShellSphere);
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("distanceShellSphere", &m_distanceShellSphere, SHADER_FLOAT);
		}
	}


	void PointCloud::NotifyKeyPressed( const Events::KeyboardEvent& event)
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(GetMaterial()->GetShaderList());

		if(event.GetEventType() == Events::KeyboardEventType::KEY_PRESSED)
		{
			if (event.GetKey() == 'x')
			{
				m_selectedAxe = XAXE_SELECTED;
			}
			else if (event.GetKey() == 'y')
			{
				m_selectedAxe = YAXE_SELECTED;
			}
			else if (event.GetKey() == 'z')
			{
				m_selectedAxe = ZAXE_SELECTED;
			}
			else if (event.GetKey() == 'c')
			{
				m_selectedAxe = DISTANCESHELLSPHERE_SELECTED;
			}
			else if (event.GetSpecialKey() == Events::KEY_RIGHT)
			{
				switch (m_selectedAxe)
				{
					case XAXE_SELECTED:
					{
						m_xMin += DELTA;
						if (m_xMin > m_xMax)
							m_xMin = m_xMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMin", &m_xMin, SHADER_FLOAT);
						break;
					}

					case YAXE_SELECTED:
					{
						m_yMin += DELTA;
						if (m_yMin > m_yMax)
							m_yMin = m_yMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMin", &m_yMin, SHADER_FLOAT);
						break;
					}

					case ZAXE_SELECTED:
					{
						m_zMin += DELTA;
						if (m_zMin > m_zMax)
							m_zMin = m_zMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMin", &m_zMin, SHADER_FLOAT);
						break;
					}

					default:
						break;
				}
			}
			else if (event.GetSpecialKey() == Events::KEY_LEFT)
			{
				switch (m_selectedAxe)
				{
				case XAXE_SELECTED:
					{
						m_xMin -= DELTA;
						if (m_xMin < m_aabb.m_minBounds.x)
							m_xMin = m_aabb.m_minBounds.x;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMin", &m_xMin, SHADER_FLOAT);
						break;
					}

				case YAXE_SELECTED:
					{
						m_yMin -= DELTA;
						if (m_yMin < m_aabb.m_minBounds.y)
							m_yMin = m_aabb.m_minBounds.y;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMin", &m_yMin, SHADER_FLOAT);
						break;
					}

				case ZAXE_SELECTED:
					{
						m_zMin -= DELTA;
						if (m_zMin < m_aabb.m_minBounds.z)
							m_zMin = m_aabb.m_minBounds.z;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMin", &m_zMin, SHADER_FLOAT);
						break;
					}

				default:
					break;
				}
			}
			else if (event.GetSpecialKey() == Events::KEY_UP)
			{
				switch (m_selectedAxe)
				{
				case XAXE_SELECTED:
					{
						m_xMax += DELTA;
						if (m_xMax > m_aabb.m_maxBounds.x)
							m_xMax = m_aabb.m_maxBounds.x;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMax", &m_xMax, SHADER_FLOAT);
						break;
					}

				case YAXE_SELECTED:
					{
						m_yMax += DELTA;
						if (m_yMax > m_aabb.m_maxBounds.y)
							m_yMax = m_aabb.m_maxBounds.y;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMax", &m_yMax, SHADER_FLOAT);
						break;
					}

				case ZAXE_SELECTED:
					{
						m_zMax += DELTA;
						if (m_zMax > m_aabb.m_maxBounds.z)
							m_zMax = m_aabb.m_maxBounds.z;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMax", &m_zMax, SHADER_FLOAT);
						break;
					}

				case DISTANCESHELLSPHERE_SELECTED:
					{
						m_distanceShellSphere += DELTA;

						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("distanceShellSphere", &m_distanceShellSphere, SHADER_FLOAT);
						break;
					}

				default:
					break;
				}
			}
			else if (event.GetSpecialKey() == Events::KEY_DOWN)
			{
				switch (m_selectedAxe)
				{
				case XAXE_SELECTED:
					{
						m_xMax -= DELTA;
						if (m_xMin > m_xMax)
							m_xMin = m_xMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("xMax", &m_xMax, SHADER_FLOAT);
						break;
					}

				case YAXE_SELECTED:
					{
						m_yMax -= DELTA;
						if (m_yMin > m_yMax)
							m_yMin = m_yMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("yMax", &m_yMax, SHADER_FLOAT);
						break;
					}

				case ZAXE_SELECTED:
					{
						m_zMax -= DELTA;
						if (m_zMin > m_zMax)
							m_zMin = m_zMax;
						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("zMax", &m_zMax, SHADER_FLOAT);
						break;
					}

				case DISTANCESHELLSPHERE_SELECTED:
					{
						m_distanceShellSphere -= DELTA;
						if (m_distanceShellSphere < 0.0f)
							m_distanceShellSphere = 0.0f;

						GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("distanceShellSphere", &m_distanceShellSphere, SHADER_FLOAT);
						break;
					}

				default:
					break;
				}
			}
		}
	}

	void PointCloud::NotifyMouseMoved( const Events::MouseEvent& event )
	{
	}

	void PointCloud::NotifyMouseClicked( const Events::MouseEvent& event )
	{
		// If we are scrolling == Zooming
		if(event.GetType() == Events::MouseEventType::SCROLL_DOWN)
		{
			glm::vec3 cameraPosition = Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetPosition();
			glm::vec3 objectPosition = m_transform.GetPosition();
			float distance = glm::length(objectPosition - cameraPosition);
			float pointSize = 20.0f/(distance+1.0f);

			LowLevelGraphics::LowLevelAPI::BindShaders(GetMaterial()->GetShaderList());
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("pointSize", &pointSize, SHADER_FLOAT);
		}
		else if(event.GetType() == Events::MouseEventType::SCROLL_UP)
		{
			glm::vec3 cameraPosition = Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetPosition();
			glm::vec3 objectPosition = m_transform.GetPosition();
			float distance = glm::length(objectPosition - cameraPosition);
			float pointSize = 20.0f/(distance+1.0f);

			LowLevelGraphics::LowLevelAPI::BindShaders(GetMaterial()->GetShaderList());
			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("pointSize", &pointSize, SHADER_FLOAT);
		}

		LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, glm::value_ptr(Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetViewMatrix()), SHADER_MATRIX44);
	}
} // namespace SceneManager
} // namespace Atum


#endif
