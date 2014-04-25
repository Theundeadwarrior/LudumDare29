#ifndef SCENEMANAGER_TRANSFORM_H
#define SCENEMANAGER_TRANSFORM_H

#include "GLM/include/glm/glm.hpp"
#include "GLM/include/glm/gtx/quaternion.hpp"

namespace Atum
{
namespace SceneManager
{
	class Transform
	{
	public:
		Transform(const glm::vec3& position = glm::vec3(0,0,0), const glm::mat4x4& rotation = glm::mat4(), const glm::vec3& scale = glm::vec3(1,1,1));
		Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
		Transform(const glm::vec3& position, const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ, const glm::vec3& scale);
		~Transform();

		void Rotate(const glm::mat4x4& rotation);
		void Rotate(const glm::quat& quaternion);
		void SetRotation(const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ);
		void SetRotation(const glm::mat4x4& rotation);
		void SetRotation(const glm::quat& quaternion);
		void Scale(const glm::vec3& scale);
		void SetScale(const glm::vec3& scale);
		void Translate(const glm::vec3& translation);
		void SetTranslate(const glm::vec3& translation);
		void UpdateMatrices();

		void GetMatrix(glm::mat4x4& matrix) const;
		glm::mat4x4 GetMatrix() const;

		void GetInverseMatrix(glm::mat4x4& matrix) const;
		glm::mat4x4 GetInverseMatrix() const;

		glm::vec3 GetPosition() const {return m_position;}
		glm::vec3 GetScale() const {return m_scale;}
		glm::quat GetRotation() const {return glm::quat_cast(m_rotationMatrix);}

	private:
		void CalculateTransformMatrix(glm::mat4x4& matrix) const;
		void CalculateInverseMatrix(glm::mat4x4& matrix) const;

	private:
		bool m_isDirty;
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::mat4x4 m_rotationMatrix;
		glm::mat4x4 m_transformMatrix;
		glm::mat4x4 m_inverseTransformMatrix;
	};

} // namespace SceneManager
} // namespace Atum


#endif
