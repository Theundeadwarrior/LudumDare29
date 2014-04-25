#include "PerspectiveCamera.h"
#include "LowLevelGraphics/Material/Shader/Shader.h"
#include "GLM/include/glm/gtc/matrix_transform.hpp"

namespace Atum
{
namespace SceneManager
{	
	//-----------------------------------------------------------------------------
	PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraParams& params, const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up)
	: Camera(position, POI, up)
	{
		m_fovy = params.fovy;
		m_aspectRatio = params.aspectRatio;
		m_near = params.nearZ;
		m_far = params.farZ;
		m_perspective = glm::perspective(m_fovy, m_aspectRatio, m_near, m_far);
	}

	//-----------------------------------------------------------------------------
	void PerspectiveCamera::GetPerspectiveMat(glm::mat4x4& matrix) const
	{
		matrix = m_perspective;
	}

	//-----------------------------------------------------------------------------
	float PerspectiveCamera::GetFovy() const
	{
		return m_fovy;
	}

	//-----------------------------------------------------------------------------
	float PerspectiveCamera::GetAspectRatio() const
	{
		return m_aspectRatio;
	}

	//-----------------------------------------------------------------------------
	float PerspectiveCamera::GetNear() const
	{
		return m_near;
	}

	//-----------------------------------------------------------------------------
	float PerspectiveCamera::GetFar() const
	{
		return m_far;
	}

	//-----------------------------------------------------------------------------
	void PerspectiveCamera::SetFovy(float value)
	{
		m_fovy = value;
		m_perspective = glm::perspective(m_fovy, m_aspectRatio, m_near, m_far);
	}

	//-----------------------------------------------------------------------------
	void PerspectiveCamera::SetAspectRatio(float value)
	{
		m_aspectRatio = value;
		m_perspective = glm::perspective(m_fovy, m_aspectRatio, m_near, m_far);
	}

	//-----------------------------------------------------------------------------
	void PerspectiveCamera::SetNear(float value)
	{
		m_near = value;
		m_perspective = glm::perspective(m_fovy, m_aspectRatio, m_near, m_far);
	}

	//-----------------------------------------------------------------------------
	void PerspectiveCamera::SetFar(float value)
	{
		m_far = value;
		m_perspective = glm::perspective(m_fovy, m_aspectRatio, m_near, m_far);
	}

} // namespace SceneManager
} // namespace Atum