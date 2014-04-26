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
		enum GamePlayObjectType
		{
			MainCharacter,
			Platform,
			Invalid
		};

		GamePlayObject();
		virtual ~GamePlayObject();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		virtual void Init(){}
		virtual void Uninit(){}

		virtual void Update(){}
		virtual void Reset(){}

		virtual const GamePlayObjectType Intersect(const GamePlayObject& gameplayObject)const{return gameplayObject.GetGameplayObjectType();}

		virtual const GamePlayObjectType GetGameplayObjectType()const =0{return Invalid;}

	protected:
		bool m_isPositionAffectedByLevel;
	};

} // namespace SceneManager
} // namespace Atum


#endif
