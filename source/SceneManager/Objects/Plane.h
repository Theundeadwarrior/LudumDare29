#ifndef SCENEMANAGER_PLANE_H
#define SCENEMANAGER_PLANE_H

#include "Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
	namespace SceneManager
	{

		class Plane : public Object
		{
		public:
			Plane(MaterialID materialID, GeometryID geomId, const Transform& transform);
			~Plane();

			//PropertyList GetPropertyList();
			
		};

	} // namespace SceneManager
} // namespace Atum


#endif
