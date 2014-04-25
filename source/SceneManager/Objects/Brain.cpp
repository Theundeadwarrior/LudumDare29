#ifndef SCENEMANAGER_CUBE_CPP
#define SCENEMANAGER_CUBE_CPP

#include "Brain.h"
#include "Events/EventManager.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Scene/Scene.h"
#include <GLM/include/glm/gtc/type_ptr.hpp>

namespace Atum
{
namespace SceneManager
{
	Brain::Brain(MaterialID materialID, GeometryID geomId, const Transform & transform, const Utilities::AABB & aabb)
		:Object(materialID, geomId, transform, aabb)
	{
		m_sagitalPlane = (aabb.m_maxBounds.x - aabb.m_minBounds.x)/2.0f;
		m_coronalPlane = (aabb.m_minBounds.z - aabb.m_maxBounds.z)/2.0f;
		m_transversePlane = (aabb.m_maxBounds.y - aabb.m_minBounds.y)/2.0f;

		Events::EventManager::GetInstance().RegisterKeyboardListener(this);
		Events::EventManager::GetInstance().RegisterMouseListener(this);
	}

	Brain::~Brain()
	{
		Events::EventManager::GetInstance().UnregisterMouseListener(this);
		Events::EventManager::GetInstance().UnregisterKeyboardListener(this);
	}

	void Brain::NotifyKeyPressed( const Events::KeyboardEvent& event)
	{
		if(event.GetEventType() == Events::KeyboardEventType::KEY_PRESSED)
		{
			if (event.GetSpecialKey() == Events::KEY_DOWN)
			{
				m_transversePlane -= 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(1, &m_transversePlane, SHADER_FLOAT);
			}
			else if (event.GetSpecialKey() == Events::KEY_UP)
			{
				m_transversePlane += 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(1, &m_transversePlane, SHADER_FLOAT);
			}
			else if (event.GetSpecialKey() == Events::KEY_LEFT)
			{
				m_sagitalPlane -= 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(3, &m_sagitalPlane, SHADER_FLOAT);
			}
			else if (event.GetSpecialKey() == Events::KEY_RIGHT)
			{
				m_sagitalPlane += 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(3, &m_sagitalPlane, SHADER_FLOAT);
			}
			else if (event.GetKey() == 'j')
			{
				m_coronalPlane -= 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(2, &m_coronalPlane, SHADER_FLOAT);
			}
			else if (event.GetKey() == 'k')
			{
				m_coronalPlane += 0.05f;
				GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(2, &m_coronalPlane, SHADER_FLOAT);
			}
		}
	}

	void Brain::NotifyMouseMoved( const Events::MouseEvent& event )
	{
	}

	void Brain::NotifyMouseClicked( const Events::MouseEvent& event )
	{
		// If we are scrolling == Zooming
		if(event.GetType() == Events::MouseEventType::SCROLL_DOWN)
		{
			glm::vec3 cameraPosition = Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetPosition();
			glm::vec3 objectPosition = m_transform.GetPosition();
			float distance = glm::length(objectPosition - cameraPosition);

			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(0, &distance, SHADER_FLOAT);
		}
		else if(event.GetType() == Events::MouseEventType::SCROLL_UP)
		{
			glm::vec3 cameraPosition = Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetPosition();
			glm::vec3 objectPosition = m_transform.GetPosition();
			float distance = glm::length(objectPosition - cameraPosition);

			GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(0, &distance, SHADER_FLOAT);
		}

		LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, glm::value_ptr(Atum::SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetViewMatrix()), SHADER_MATRIX44);
	}
} // namespace SceneManager
} // namespace Atum


#endif
