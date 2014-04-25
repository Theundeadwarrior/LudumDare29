#ifndef SCENEMANAGER_TORUS_H
#define SCENEMANAGER_TORUS_H

#include "Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{

	class Torus : public Object
	{
	public:
		Torus();
		~Torus();

		PropertyList GetPropertyList();
	};

} // namespace SceneManager
} // namespace Atum


#endif