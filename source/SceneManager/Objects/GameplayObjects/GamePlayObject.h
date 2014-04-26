#ifndef SCENEMANAGER_GAMEPLAYOBJECT_H
#define SCENEMANAGER_GAMEPLAYOBJECT_H

#include "SceneManager/Objects/Object.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{

	class GamePlayObject : public Object
	{
	public:
		GamePlayObject(MaterialID materialID, const Transform& transform);
		~GamePlayObject();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		virtual void Update()=0{}
		virtual void Reset(){}

	protected:
		bool m_isPositionAffectedByLevel;
	};

} // namespace SceneManager
} // namespace Atum


#endif
