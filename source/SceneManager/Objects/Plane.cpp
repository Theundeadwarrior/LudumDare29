#ifndef SCENEMANAGER_PLANE_CPP
#define SCENEMANAGER_PLANE_CPP

#include "Plane.h"

namespace Atum
{
namespace SceneManager
{

	Plane::Plane(MaterialID materialID, GeometryID geomId, const Transform& transform)
		:Object(materialID, geomId, transform)
	{

	}

	Plane::~Plane()
	{

	}

} // namespace SceneManager
} // namespace Atum


#endif
