#include "OBB.h"

#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b

namespace Atum
{
namespace Utilities
{
	OBB::OBB()
	{
		m_corners.reserve(8);
	}

	void OBB::UpdateBoundingBox(const std::vector<glm::vec3>& geom)
	{
		glm::vec3 minBounds(999999, 999999, 999999);
		glm::vec3 maxBounds(-999999, -999999, -999999);

		for(int i=0; i<geom.size(); i++)
		{
			glm::vec3 vertex = geom[i];

			minBounds.x = min(minBounds.x,vertex.x);
			minBounds.y = min(minBounds.y, vertex.y);
			minBounds.z = min(minBounds.z, vertex.z);
			maxBounds.x = max(maxBounds.x, vertex.x);
			maxBounds.y = max(maxBounds.y, vertex.y);
			maxBounds.z = max(maxBounds.z, vertex.z);
		}

		//Vary if fucks
		if(maxBounds.x == minBounds.x)
		{
			maxBounds.x += OBB_EPSILON;
			minBounds.x -= OBB_EPSILON;
		}
		if(maxBounds.y == minBounds.y)
		{
			maxBounds.y += OBB_EPSILON;
			minBounds.y -= OBB_EPSILON;
		}
		if(maxBounds.z == minBounds.z)
		{
			maxBounds.z += OBB_EPSILON;
			minBounds.z -= OBB_EPSILON;
		}

		m_corners.push_back(glm::vec3(minBounds.x, maxBounds.y, minBounds.z));
		m_corners.push_back(glm::vec3(maxBounds.x, maxBounds.y, minBounds.z));
		m_corners.push_back(glm::vec3(minBounds.x, minBounds.y, minBounds.z));
		m_corners.push_back(glm::vec3(maxBounds.x, minBounds.y, minBounds.z));
		m_corners.push_back(glm::vec3(minBounds.x, maxBounds.y, maxBounds.z));
		m_corners.push_back(glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z));
		m_corners.push_back(glm::vec3(minBounds.x, minBounds.y, maxBounds.z));
		m_corners.push_back(glm::vec3(maxBounds.x, minBounds.y, maxBounds.z));
	}

	OBB::~OBB()
	{
	}

}
}