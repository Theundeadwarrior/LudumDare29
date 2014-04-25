#ifndef UTILITIES_OBB_H
#define UTILITIES_OBB_H

#include "GLM/include/glm/glm.hpp"
#include <vector>

#define OBB_EPSILON 0.1

namespace Atum { namespace SceneManager { class PropertyList; class Transform; }}

namespace Atum
{
namespace Utilities
{
	class OBB
	{
	public:
		OBB();
		~OBB();
        void UpdateBoundingBox(const std::vector<glm::vec3>& geom);
		const std::vector<glm::vec3>* const GetCorners() const { return &m_corners;  }

	private:
		std::vector<glm::vec3> m_corners;
	};

} // namespace Utilities
} // namespace Atum


#endif