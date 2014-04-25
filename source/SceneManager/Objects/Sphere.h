#ifndef SCENEMANAGER_SPHERE_H
#define SCENEMANAGER_SPHERE_H

#include "Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
	namespace SceneManager
	{

		class Sphere : public Object
		{
		public:
			Sphere();
			~Sphere();

			PropertyList GetPropertyList();
		};

	} // namespace SceneManager
} // namespace Atum


#endif