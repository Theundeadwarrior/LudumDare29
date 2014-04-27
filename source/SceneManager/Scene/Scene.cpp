#include "Scene.h"
#include <iostream>
#include "Events\EventManager.h"
#include "LowLevelGraphics\Material\Shader\Shader.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace SceneManager
{
	Scene::Scene()
	: m_currentCamera(NULL)
	, m_mouseClickPositionX(-1)
	, m_mouseClickPositionY(-1)
	, m_cameraMode(CAMERA_NONE)
	, m_skyBox(0)
	{
		Events::EventManager::GetInstance().RegisterMouseListener(this);
	}

	void Scene::AddCamera( Camera* const camera )
	{
		m_cameraList.push_back(camera);

		// In case this is the first camera, we want to set it current by default.
		// Maybe we should include a constructor with a default camera and one with
		// a camera parameter.
		if(m_cameraList.size() == 1)
		{
			SetCurrentCamera(0);
		}
	}

	void Scene::AddPointLight(PointLight* pointLight)
	{
		if(m_pointLightList.size() < 5)
		{
			pointLight->SetIndex(m_pointLightList.size());
			m_pointLightList.push_back(pointLight);
			UpdateAllPointLights();
		}
		else
		{
			ATUM_ERROR("Reached Max Point Lights. Light not added.");
		}
	}

	/*void Scene::DeletePointLight(PointLight* pointLight)
	{

	}*/

	/*void Scene::UpdateIndexes(std::vector<Light*>* lights)
	{
		for(int i = 0; i<lights->size(); i++)
		{
			lights->at(i)->SetIndex(i);
		}
	}*/

	void Scene::AddSkyBox(SkyBox * skyBox)
	{
		m_skyBox = skyBox;
	}

	SkyBox * const Scene::GetSkyBox() const
	{
		return m_skyBox;
	}

	void Scene::UpdateAllPointLights()
	{
		int size = m_pointLightList.size();
		LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSSIZE, &size, SHADER_INT);
		//PointLight* light = m_pointLightList.at(0)
		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSDIFFUSE, &(light->GetDiffuse()), SHADER_LIGHT_DIFFUSE);

		for(int i = 0; i<m_pointLightList.size(); i++)
		{
			PointLight* light = m_pointLightList.at(i);
			float rad = light->GetRadius();
			LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSDIFFUSE, &(light->GetDiffuse()), i, SHADER_LIGHT_DIFFUSE);
			LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSAMBIENT, &(light->GetAmbient()), i, SHADER_LIGHT_AMBIENT);
			LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSSPECULAR, &(light->GetSpecular()), i, SHADER_LIGHT_SPECULAR);
			LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSRADIUS, &rad, i, SHADER_LIGHT_RADIUS);
			LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSTRANSFORM, &(light->GetTransform()->GetMatrix()), i, SHADER_LIGHT_TRANSFORM);
		}
	}

	void Scene::UpdateAllObjects()
	{
		std::list<Object*>::iterator it = m_objectList.begin();
		std::list<Object*>::iterator endit = m_objectList.end();

		for (; it != endit; ++it)
		{
			// The object might have been deleted
			if ((*it)->GetState() == Object::E_ToDelete)
			{
				delete *it;
				it = m_objectList.erase(it);
				
				if (it == endit)
				{
					break;
				}
			}
			else
			{
				(*it)->Update();
			}
		}
	}

	void Scene::NotifyMouseClicked( const Events::MouseEvent& event )
	{
		//// If we are scrolling == Zooming
		//if(event.GetType() == Events::MouseEventType::SCROLL_DOWN)
		//{
		//	glm::vec3 currentPosition = m_currentCamera->GetPosition();
		//	m_currentCamera->SetPosition(currentPosition - 0.5f * m_currentCamera->GetLookAt());
		//}
		//else if(event.GetType() == Events::MouseEventType::SCROLL_UP)
		//{
		//	glm::vec3 currentPosition = m_currentCamera->GetPosition();
		//	m_currentCamera->SetPosition(currentPosition + 0.5f * m_currentCamera->GetLookAt());
		//}

		//// if we are clicking right and dragging == rotate
		//if(event.GetClickType() == Events::MouseClick::RIGHT_CLICK && event.GetType() == Events::MouseEventType::MOUSE_DOWN)
		//{
		//	m_cameraMode = CAMERA_ROTATION;	
		//	m_mouseClickPositionX = event.GetXPosition();
		//	m_mouseClickPositionY = event.GetYPosition();
		//}

		//if(event.GetClickType() == Events::MouseClick::MIDDLE_CLICK && event.GetType() == Events::MouseEventType::MOUSE_DOWN)
		//{
		//	m_cameraMode = CAMERA_TRANSLATION;
		//	m_mouseClickPositionX = event.GetXPosition();
		//	m_mouseClickPositionY = event.GetYPosition();
		//}

		//if((event.GetClickType() == Events::MouseClick::RIGHT_CLICK || event.GetClickType() == Events::MouseClick::MIDDLE_CLICK)
		//	&& event.GetType() == Events::MouseEventType::MOUSE_UP)
		//{
		//	m_cameraMode = CAMERA_NONE;	
		//	m_mouseClickPositionX = -1;
		//	m_mouseClickPositionY = -1;
		//}

		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, &m_currentCamera->GetViewMatrix(), SHADER_MATRIX44);
	}

	void Scene::NotifyMouseMoved( const Events::MouseEvent& event )
	{
		//const float PI = 3.1415926535897932384626433832795f;
		//const float EPSILON = 0.001;

		//// TRANSLATION
		//if(event.GetType() == Events::MouseEventType::MOUSE_MOTION_ONLY && m_cameraMode == CAMERA_TRANSLATION)
		//{
		//	const float sensibility = 1/100.0f;

		//	float deltaX = event.GetXPosition() - m_mouseClickPositionX; 
		//	float deltaY = event.GetYPosition() - m_mouseClickPositionY; 
		//	m_mouseClickPositionX = event.GetXPosition();
		//	m_mouseClickPositionY = event.GetYPosition();

		//	glm::vec3 currentUp = glm::normalize(m_currentCamera->GetUp());
		//	glm::vec3 currenRight = glm::normalize(glm::cross(m_currentCamera->GetLookAt(),currentUp));

		//	glm::vec3 newPosition = m_currentCamera->GetPosition() -deltaX * sensibility * currenRight + deltaY * sensibility * currentUp;
		//	glm::vec3 newPOI = m_currentCamera->GetPOI() - deltaX * sensibility * currenRight + deltaY * sensibility * currentUp;

		//	m_currentCamera->SetViewMatrix(newPosition, newPOI, currentUp);
		//	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, &m_currentCamera->GetViewMatrix(), SHADER_MATRIX44);			
		//}

		//// ROTATION
		//if(event.GetType() == Events::MouseEventType::MOUSE_MOTION_ONLY && m_cameraMode == CAMERA_ROTATION)
		//{
		//	float deltaX = event.GetXPosition() - m_mouseClickPositionX; 
		//	float deltaY = event.GetYPosition() - m_mouseClickPositionY; 
		//	m_mouseClickPositionX = event.GetXPosition();
		//	m_mouseClickPositionY = event.GetYPosition();

		//	glm::vec3 camPosition = m_currentCamera->GetPosition();
		//	glm::vec3 currentLookAt = m_currentCamera->GetLookAt();

		//	float t = -camPosition.y / currentLookAt.y;
		//	glm::vec3 POI(camPosition + t * currentLookAt);
		//	glm::vec3 relativePosition = camPosition - POI;

		//	// We go into spherical coordinate system
		//	float r = sqrt(pow(relativePosition.x,2) + pow(relativePosition.y,2) + pow(relativePosition.z,2));
		//	float theta = acos(relativePosition.y / r);
		//	float phi = atan2(relativePosition.x, relativePosition.z);

		//	phi -= deltaX/200.0f;
		//	theta -= deltaY/100.0f;

		//	if(theta < 0)
		//	{
		//		theta  = EPSILON;
		//	}
		//	else if(theta > PI)
		//	{
		//		theta = PI - EPSILON;
		//	}

		//	glm::vec3 newPosition( r * sin(theta) * sin(phi) + POI.x, r * cos(theta) + POI.y, r * sin(theta) * cos(phi) + POI.z);
		//	glm::vec3 newLookAt(glm::normalize(POI - newPosition));
		//	glm::vec3 newRight = glm::normalize(glm::cross(newLookAt, glm::vec3(0,1,0)));
		//	glm::vec3 newUp = glm::cross(newRight,newLookAt);

		//	m_currentCamera->SetViewMatrix(newPosition, POI, newUp);
		//	LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, &m_currentCamera->GetViewMatrix(), SHADER_MATRIX44);
		//}
	}

	Camera* const Scene::GetCurrentCamera() const
	{
		return m_currentCamera;
	}

	Scene::~Scene()
	{
		Events::EventManager::GetInstance().UnregisterMouseListener(this);
	}

	void Scene::Update()
	{
		UpdateAllObjects();
	}

} // namespace SceneManager
} // namespace Atum

