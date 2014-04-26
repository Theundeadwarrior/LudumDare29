#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"
#include "SceneManager/SceneManager.h"

namespace Atum
{
namespace SceneManager
{
	GamePlayObject::GamePlayObject(MaterialID materialID, const Transform& transform)
		:Object(materialID, 
		SceneManager::GetInstance().GetGeometryManager()->GetStandardPlaneGeometryId(), 
		transform)
		,m_isPositionAffectedByLevel(true)
	{}

	GamePlayObject::~GamePlayObject()
	{}

	void GamePlayObject::GetPropertyList( PropertyList& o_properties )
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties

	}

	void GamePlayObject::UpdatePropertyList( PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties
	}

} // namespace SceneManager
} // namespace Atum
