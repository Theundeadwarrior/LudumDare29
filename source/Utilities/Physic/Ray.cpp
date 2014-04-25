#include "Ray.h"

namespace Atum
{
namespace Utilities
{

Ray::Ray()
{}

Ray::~Ray()
{}

Ray::Ray(const Ray& ray)
	:m_origin(ray.m_origin),
	m_direction(ray.m_direction)
{}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction)
	: m_origin(origin),
	m_direction(glm::normalize(direction))
{}

Ray &Ray::operator= (const Ray &ray)
{
    m_origin = ray.m_origin;
    m_direction = ray.m_direction;

    return *this;
}

glm::vec3 Ray::GetPoint (float distance) const
{
    return m_origin + m_direction * distance;
}

glm::vec3 Ray::operator* (float distance) const
{
    return GetPoint(distance);
}

inline void Ray::SetOrigin(const glm::vec3 &origin)
{
	m_origin = origin;
}

glm::vec3 Ray::GetOrigin() const
{
	return m_origin;
}

void Ray::SetDirection(const glm::vec3 &direction)
{
	m_direction = glm::normalize(direction);
}

glm::vec3 Ray::GetDirection() const
{
	return m_direction;
}

}
}