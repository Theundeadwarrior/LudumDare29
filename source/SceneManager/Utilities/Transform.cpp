#include "Transform.h"
#include "GLM/include/glm/gtc/matrix_inverse.hpp"
#include "GLM/include/glm/gtx/transform.hpp"

#include "Utilities/Debug/Debug.h"


namespace Atum
{
namespace SceneManager
{
//-----------------------------------------------------------------------------
Transform::Transform( const glm::vec3& position, const glm::mat4x4& rotation, const glm::vec3& scale)
	: m_isDirty(true)
	, m_position(position)
	, m_scale(scale)
	, m_rotationMatrix(rotation)
{
	UpdateMatrices();
}

//-----------------------------------------------------------------------------
Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
	: m_isDirty(true)
{
	*this = Transform(position, glm::mat4x4(glm::mat4_cast(rotation)), scale);
	UpdateMatrices();
}

//-----------------------------------------------------------------------------
Transform::Transform( const glm::vec3& position, const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ, const glm::vec3& scale )
	: m_isDirty(true)
	, m_position(position)
	, m_scale(scale)
{
	SetRotation(axisX, axisY, axisZ);
	UpdateMatrices();
}

//-----------------------------------------------------------------------------
Transform::~Transform()
{

}

//-----------------------------------------------------------------------------
void Transform::Rotate(const glm::mat4x4& rotation)
{
	m_rotationMatrix *= rotation;
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::Rotate(const glm::quat& quaternion)
{
	m_rotationMatrix *= glm::mat4x4(glm::mat4_cast(quaternion));
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::SetRotation(const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ)
{
	glm::mat4x4 rotation(axisX.x, axisX.y, axisX.z, 0, axisY.x, axisY.y, axisY.z, 0, axisZ.x, axisZ.y, axisZ.z, 0, 0, 0, 0, 1);
	SetRotation(rotation);
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::SetRotation( const glm::mat4x4& rotation )
{
	m_rotationMatrix = rotation;
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::SetRotation(const glm::quat& quaternion)
{
	m_rotationMatrix = glm::mat4_cast(quaternion);
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::Scale(const glm::vec3& scale)
{
	m_scale *= scale;
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::Translate(const glm::vec3& translation)
{
	m_position += translation;
	m_isDirty = true;
}

//-----------------------------------------------------------------------------
void Transform::SetTranslate(const glm::vec3& translation)
{
	m_position = translation;
	m_isDirty = true;
}
//-----------------------------------------------------------------------------
void Transform::UpdateMatrices()
{
	if(m_isDirty)
	{
		CalculateTransformMatrix(m_transformMatrix);
		CalculateInverseMatrix(m_inverseTransformMatrix);
		m_isDirty = false;
	}
}
//-----------------------------------------------------------------------------
void Transform::GetMatrix(glm::mat4x4& matrix) const	
{
	ATUM_ASSERT_MESSAGE(!m_isDirty,"Transform matrix is not updated, use UpdateMatrices");
	matrix = m_transformMatrix;
}

//-----------------------------------------------------------------------------
glm::mat4x4 Transform::GetMatrix() const
{
	ATUM_ASSERT_MESSAGE(!m_isDirty,"Transform matrix is not updated, use UpdateMatrices");
	return m_transformMatrix;
}

//-----------------------------------------------------------------------------
void Transform::CalculateTransformMatrix( glm::mat4x4& matrix ) const
{
	matrix = glm::mat4();
	matrix[0][0] = m_scale.x;
	matrix[1][1] = m_scale.y;
	matrix[2][2] = m_scale.z;
	matrix[3][3] = 1.0f;
	matrix*=m_rotationMatrix;
	matrix[3][0] = m_position.x;
	matrix[3][1] = m_position.y;
	matrix[3][2] = m_position.z;
}

//-----------------------------------------------------------------------------
void Transform::GetInverseMatrix(glm::mat4x4& matrix) const
{
	ATUM_ASSERT_MESSAGE(!m_isDirty,"Transform matrix is not updated, use UpdateMatrices");
	matrix = m_inverseTransformMatrix;
}

//-----------------------------------------------------------------------------
glm::mat4x4 Transform::GetInverseMatrix() const
{
	ATUM_ASSERT_MESSAGE(!m_isDirty,"Transform matrix is not updated, use UpdateMatrices");
	return m_inverseTransformMatrix;
}

//-----------------------------------------------------------------------------
void Transform::CalculateInverseMatrix(glm::mat4x4& matrix) const
{
	matrix = glm::mat4();
	glm::mat4x4 rotMat(m_rotationMatrix[0][0], m_rotationMatrix[0][1], m_rotationMatrix[0][2],0,
		m_rotationMatrix[1][0], m_rotationMatrix[1][1], m_rotationMatrix[1][2], 0,
		m_rotationMatrix[2][0], m_rotationMatrix[2][1], m_rotationMatrix[2][2], 0,
		0,0,0,1);

	glm::vec4 invPos = rotMat * glm::vec4(m_position,1);

	matrix[0][0] = m_scale.x;
	matrix[1][1] = m_scale.y;
	matrix[2][2] = m_scale.z;
	matrix[3][3] = 1;

	matrix*=rotMat;

	matrix[3][0] = -invPos.x;
	matrix[3][1] = -invPos.y;
	matrix[3][2] = -invPos.z;
}

} // namespace SceneManager
} // namespace Atum
