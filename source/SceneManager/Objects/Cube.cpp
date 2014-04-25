#ifndef SCENEMANAGER_CUBE_CPP
#define SCENEMANAGER_CUBE_CPP

#include "Cube.h"
#include "SceneManager/SceneManager.h"

namespace Atum
{
namespace SceneManager
{
	Cube::Cube(MaterialID materialID, const Transform& transform)
		:Object(materialID, 
		SceneManager::GetInstance().GetGeometryManager()->GetStandardCubeGeometryId(), 
		transform)
	{}

	Cube::~Cube()
	{}

	void Cube::GetPropertyList( PropertyList& o_properties )
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties

	}

	void Cube::UpdatePropertyList( PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties
	}

} // namespace SceneManager
} // namespace Atum


#endif
