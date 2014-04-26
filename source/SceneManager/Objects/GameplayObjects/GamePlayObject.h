#ifndef SCENEMANAGER_GAMEPLAYOBJECT_H
#define SCENEMANAGER_GAMEPLAYOBJECT_H

#include "SceneManager/Objects/Object.h"
#include "SceneManager/Manager/TypedefID.h"

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

		virtual void Init();
		virtual void Uninit(){}

		virtual void Update(){}
		virtual void Reset(){}

		virtual const GamePlayObjectType Intersect(const GamePlayObject& gameplayObject)const{return gameplayObject.GetGameplayObjectType();}

		virtual const GamePlayObjectType GetGameplayObjectType()const =0{return Invalid;}

		virtual TextureId GetTexture()=0{return -1;}
		virtual MaterialID GetMaterial()=0{return -1;}

		static ShaderListID GetShader();
		static GeometryID GetQuad();

	protected:
		bool m_isPositionAffectedByLevel;
		glm::vec4 m_currentPosition;
		glm::vec4 m_scale;
	};

} // namespace SceneManager
} // namespace Atum


#endif
