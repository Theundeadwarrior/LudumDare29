#ifndef SCENEMANAGER_MESH_H
#define SCENEMANAGER_MESH_H

#include "Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
	namespace SceneManager
	{

		class Mesh : public Object
		{
		public:
			Mesh();
			~Mesh();

			PropertyList GetPropertyList();
		};

	} // namespace SceneManager
} // namespace Atum


#endif