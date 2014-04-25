#include "AABB.h"
#include "SceneManager/Utilities/Transform.h"

#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b

namespace Atum
{
namespace Utilities
{
	AABB::AABB()
	:m_minBounds(DEFAULT_MIN_BOUNDS,DEFAULT_MIN_BOUNDS,DEFAULT_MIN_BOUNDS),
	m_maxBounds(DEFAULT_MAX_BOUNDS,DEFAULT_MAX_BOUNDS,DEFAULT_MAX_BOUNDS)
	{
	}

	AABB::AABB(const glm::vec3 & minBounds, const glm::vec3 & maxBounds)
	{
		m_minBounds = minBounds;
		m_maxBounds = maxBounds;
	}

	void AABB::UpdateBoundingBox(const std::vector<glm::vec3>& geom, const Atum::SceneManager::Transform& transform)
	{
		m_minBounds = glm::vec3(DEFAULT_MIN_BOUNDS,DEFAULT_MIN_BOUNDS,DEFAULT_MIN_BOUNDS);
		m_maxBounds = glm::vec3(DEFAULT_MAX_BOUNDS,DEFAULT_MAX_BOUNDS,DEFAULT_MAX_BOUNDS);

		for(int i=0; i<geom.size(); i++)
		{
			glm::vec4 vertex;
			vertex.x = geom[i].x;
			vertex.y = geom[i].y;
			vertex.z = geom[i].z;
			vertex.w = 1;
			
			glm::mat4x4 transfMat;
			transform.GetMatrix(transfMat);
			vertex = transfMat * vertex;

			m_minBounds.x = min(m_minBounds.x, vertex.x);
			m_minBounds.y = min(m_minBounds.y, vertex.y);
			m_minBounds.z = min(m_minBounds.z, vertex.z);
			m_maxBounds.x = max(m_maxBounds.x, vertex.x);
			m_maxBounds.y = max(m_maxBounds.y, vertex.y);
			m_maxBounds.z = max(m_maxBounds.z, vertex.z);
			}

		if(m_maxBounds.x == m_minBounds.x)
			{
			m_maxBounds.x += OBB_EPSILON;
			m_minBounds.x -= OBB_EPSILON;
			}
		if(m_maxBounds.y == m_minBounds.y)
			{
			m_maxBounds.y += OBB_EPSILON;
			m_minBounds.y -= OBB_EPSILON;
			}
		if(m_maxBounds.z == m_minBounds.z)
			{
			m_maxBounds.z += OBB_EPSILON;
			m_minBounds.z -= OBB_EPSILON;
			}
		}

    void AABB::UpdateBoundingBox(const OBB& obb, const Atum::SceneManager::Transform& transform)
	{
		UpdateBoundingBox(*(obb.GetCorners()), transform);
	}

	AABB::~AABB()
	{
	}
}
}