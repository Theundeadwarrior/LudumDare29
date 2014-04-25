#ifndef OBJECTSELECTION_RAY_H_
#define OBJECTSELECTION_RAY_H_

#include "GLM/include/glm/glm.hpp"

namespace Atum
{
namespace Utilities
{
	class Ray
	{
		public:

			Ray();
			Ray(const Ray& ray);
			Ray(const glm::vec3 &origin, const glm::vec3 &direction);
			~Ray();

			Ray &operator= (const Ray &ray);

			glm::vec3 GetOrigin() const;
			glm::vec3 GetDirection() const;

			void SetOrigin(const glm::vec3 &origin);
			void SetDirection(const glm::vec3 &direction);

			glm::vec3 GetPoint(float distance) const;
			glm::vec3 operator*(float distance) const;

		private:

			glm::vec3 m_origin;
			glm::vec3 m_direction;
	};

}
}

#endif //__RAY_H_
