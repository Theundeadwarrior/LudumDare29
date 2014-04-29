#ifndef SCENEMANAGER_CAMERA_CPP
#define SCENEMANAGER_CAMERA_CPP

#include "Camera.h"
#include "SceneManager/Properties/PropertyList.h"
#include "GLM/include/glm/gtc/matrix_transform.hpp"


namespace Atum
{
namespace SceneManager
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up)
	: m_position(position)
	, m_POI(POI)
	, m_up(up)
	{
	}

	void Camera::GetViewMatrix(glm::mat4x4& matrix) 
	{
		m_viewMatrix = glm::lookAt(m_position, m_POI, m_up);
		matrix = m_viewMatrix;
	}


	glm::mat4x4 Camera::GetViewMatrix()
	{
		m_viewMatrix = glm::lookAt(m_position, m_POI, m_up);
		return m_viewMatrix;
	}

	void Camera::SetViewMatrix( const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up )
	{
		m_position = position;
		m_POI = POI;
		m_up = up;
	}

} // namespace SceneManager
} // namespace Atum


#endif
