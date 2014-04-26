#include "ComponentSelector.h"
#include <vector>
#include "CImg/CImg.h"
#include "GLM/include/glm/glm.hpp"

#include "LowLevelGraphics/WindowManager/WindowManager.h"

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/PerspectiveCamera.h"
#include "SceneManager/Utilities/Transform.h"

#include "Utilities/Physic/AABB.h"
#include "Utilities/Physic/Ray.h"
#include "Utilities/Physic/PhysicUtilities.h"
#include "Utilities/Math/MathUtilities.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace UserInterface
{


ComponentSelector::ComponentSelector()
	:m_selectedComponent(m_intersectedComponents.end())
{}

ComponentSelector::~ComponentSelector()
{}


void ComponentSelector::UpdateSelection( int xScreenPos, int yScreenPos )
{
	CreateIntersectionList( xScreenPos, yScreenPos );
	m_selectedComponent = m_intersectedComponents.begin();
}

bool ComponentSelector::IsComponentSelected() const
{
	return m_selectedComponent != m_intersectedComponents.end();
}

SceneManager::Component* ComponentSelector::GetSelectedComponent() const
{
	if ( IsComponentSelected() )
		return m_selectedComponent->second;
	else
		return 0;
}

void ComponentSelector::ClearSelection()
{
	m_selectedComponent = m_intersectedComponents.end();
}

void ComponentSelector::FindIntersectedComponents( const Utilities::Ray& ray )
{
	std::list<SceneManager::Object*>::iterator objIter = 
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetBeginObjectList();
	std::list<SceneManager::Object*>::iterator objIterEnd =
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetEndObjectList();

	for ( ; objIter != objIterEnd; ++objIter )
	{
		float intersectedDistance(0);
		if ( Utilities::PerformCubeHitTest
			(ray,(*objIter)->GetAABB().m_minBounds,(*objIter)->GetAABB().m_maxBounds, intersectedDistance) )
		{
			m_intersectedComponents[intersectedDistance] = *objIter;
		}
	}

	std::vector<SceneManager::Object*>::iterator pointCloudIter = 
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetBeginPointCloudList();
	std::vector<SceneManager::Object*>::iterator pointCloudIterEnd =
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetEndPointCloudList();

	for ( ; pointCloudIter != pointCloudIterEnd; ++pointCloudIter )
	{
		float intersectedDistance(0);
		if ( Utilities::PerformCubeHitTest
			(ray,(*pointCloudIter)->GetAABB().m_minBounds,(*pointCloudIter)->GetAABB().m_maxBounds, intersectedDistance) )
		{
			m_intersectedComponents[intersectedDistance] = *pointCloudIter;
		}
	}

	std::vector<ParticleSystem::ParticleSystem*>::iterator particlesIter = 
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetBeginParticleSystemList();
	std::vector<ParticleSystem::ParticleSystem*>::iterator particlesIterEnd =
		SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetEndParticleSystemList();

	for ( ; particlesIter != particlesIterEnd; ++particlesIter )
	{
		float intersectedDistance(0);
		if ( Utilities::PerformCubeHitTest
			(ray,(*particlesIter)->GetAABB().m_minBounds,(*particlesIter)->GetAABB().m_maxBounds, intersectedDistance) )
		{
			m_intersectedComponents[intersectedDistance] = *particlesIter;
		}
	}

	if ( m_isLightSelectionEnabled )
	{
		std::vector<SceneManager::PointLight*>::iterator lightIter = 
			SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetBeginPointLightList();
		std::vector<SceneManager::PointLight*>::iterator lightIterEnd =
			SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetEndPointLightList();

		for ( ; lightIter != lightIterEnd; ++lightIter )
		{
			float intersectedDistance(0);
			if ( Utilities::PerformCubeHitTest
				(ray,(*lightIter)->GetAABB().m_minBounds,(*lightIter)->GetAABB().m_maxBounds, intersectedDistance) )
			{
				m_intersectedComponents[intersectedDistance] = *lightIter;
			}
		}
	}
}

void ComponentSelector::CreateIntersectionList( unsigned int mousePosX, unsigned int mousePosY )
{
	glm::uvec2 mousePos( mousePosX, mousePosY );
	glm::vec3 worldCoordinates( Utilities::WindowToWorldCoordinates(mousePos) );

	SceneManager::Camera* camera ( SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera() );
	ATUM_ASSERT( camera != 0);
	Utilities::Ray ray ( camera->GetPosition(), glm::normalize(worldCoordinates) );

	ClearIntersectionList();
	FindIntersectedComponents( ray );
}

void ComponentSelector::ClearIntersectionList() 
{
	m_selectedComponent = m_intersectedComponents.end();
	m_intersectedComponents.clear();
}


////////////////////////////////////
void MoveComponent( SceneManager::Component* const component, unsigned int mousePosX, unsigned int mousePosY )
{
	//check the intersection between a plane (parallel to the image plane) and a ray (between the camera and the object center)
	SceneManager::Camera* camera ( SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera() );
	ATUM_ASSERT( camera != 0);
	glm::vec3 worldCoordinates( Utilities::WindowToWorldCoordinates(glm::uvec2( mousePosX, mousePosY )) );
	Utilities::Ray ray( camera->GetPosition(), glm::normalize(worldCoordinates));

	float hitDistance;

	//in case of an object or particle system
	SceneManager::Object* object( dynamic_cast<SceneManager::Object*>(component) );
	ParticleSystem::ParticleSystem* particleSystem( dynamic_cast<ParticleSystem::ParticleSystem*>(component) );
	if ( object )
	{
		if ( Utilities::PerformPlaneHitTest(ray, object->GetTransform()->GetPosition(), camera->GetLookAt(), hitDistance) )
		{
			glm::vec3 point = ray.GetPoint(hitDistance);
			object->GetTransform()->SetTranslate( point );
		}
	}
	else if(particleSystem)
	{
		if ( Utilities::PerformPlaneHitTest(ray, particleSystem->GetPosition(), camera->GetLookAt(), hitDistance) )
		{
			glm::vec3 point = ray.GetPoint(hitDistance);
			particleSystem->SetPosition(point);
			particleSystem->UpdateAABB();
		}
	}
	else
	{
		SceneManager::PointLight* light( dynamic_cast<SceneManager::PointLight*>(component));
		if ( Utilities::PerformPlaneHitTest(ray, light->GetTransform()->GetPosition(), camera->GetLookAt(), hitDistance) )
		{
			glm::vec3 point = ray.GetPoint(hitDistance);
			light->GetTransform()->SetTranslate( ray.GetPoint(hitDistance) );
			light->Update();
		}
	}
}

/////////////////////// DEBUG /////////////////////////////////

void ComponentSelector::SaveSelectionMap()
{
#ifdef _DEBUG
	glm::uvec2 windowSize( LowLevelGraphics::WindowManager::GetInstance().GetCurrentWindowSize() );
	cimg_library::CImg<unsigned char> selectionMap(windowSize.x, windowSize.y);

	SceneManager::Camera* camera ( SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetCurrentCamera() );
	ClearIntersectionList();

	for ( unsigned int i = 0; i < windowSize.x; i++ )
	{
		for ( unsigned int j = 0; j < windowSize.y; j++ )
		{
			glm::vec3 worldCoordinates( Utilities::WindowToWorldCoordinates(glm::uvec2(i,j)) );
			Utilities::Ray ray ( camera->GetPosition(), glm::normalize(worldCoordinates) );

			FindIntersectedComponents(ray);
			if ( m_intersectedComponents.size() != 0 )
			{
				if ( m_intersectedComponents.begin()->second != 0 )
					selectionMap(i,j) = m_intersectedComponents.size() * 25; 
			}
			else
			{
				selectionMap(i,j) = 0;
			}
			ClearIntersectionList();
		}
	}
	selectionMap.save("../../temp/SelectionMap.bmp");
#endif
}

}
}
