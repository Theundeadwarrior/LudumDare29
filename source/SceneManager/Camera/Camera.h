#ifndef SCENEMANAGER_CAMERA_H
#define SCENEMANAGER_CAMERA_H

#include "GLM/include/glm/glm.hpp"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up);
		virtual ~Camera(){};

		void GetViewMatrix(glm::mat4x4& matrix);
		glm::mat4x4 GetViewMatrix();
		glm::vec3 GetPosition() { return m_position; }
		glm::vec3 GetPOI() { return m_POI; }
		glm::vec3 GetLookAt() { return glm::normalize(m_POI - m_position); }
		glm::vec3 GetUp() { return m_up; }

		void SetViewMatrix(const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up);
		void SetPosition(const glm::vec3& position) { m_position = position; }

	protected:
		glm::mat4x4 m_viewMatrix;

		glm::vec3 m_position;
		glm::vec3 m_POI;
		glm::vec3 m_up;
		
	};

} // namespace SceneManager
} // namespace Atum


#endif