#ifndef SCENEMANAGER_CUBE_H
#define SCENEMANAGER_CUBE_H

#include "Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{

	class Cube : public Object
	{
		public:
			Cube(MaterialID materialID, const Transform& transform);
			~Cube();

			void GetPropertyList ( PropertyList& o_properties );
			void UpdatePropertyList ( PropertyList& i_properties );
	};

} // namespace SceneManager
} // namespace Atum


#endif
