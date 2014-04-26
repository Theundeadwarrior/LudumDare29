#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"
#include "SceneManager/SceneManager.h"

namespace Atum
{
namespace SceneManager
{
	MainCharacter::MainCharacter(MaterialID materialID, const Transform& transform)
		:GamePlayObject(materialID, 
		transform)
	{
		m_isPositionAffectedByLevel = false;
	}

	MainCharacter::~MainCharacter()
	{}

	void MainCharacter::GetPropertyList( PropertyList& o_properties )
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties

	}

	void MainCharacter::UpdatePropertyList( PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties
	}

} // namespace SceneManager
} // namespace Atum
