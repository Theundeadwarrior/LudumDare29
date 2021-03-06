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
			GamePlayObjectType_MainCharacter,
			GamePlayObjectType_Platform,
			GamePlayObjectType_Invalid
		};

		enum CharacterState
		{
			Normal,
			Dead,
			Falling,
			Jumping,
			GhostSlowed,
			WindSlowed,
			WindSped,
			WallStop
		};

		GamePlayObject();
		GamePlayObject(const glm::vec4& position, const glm::vec4& scale);
		virtual ~GamePlayObject();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		virtual void BindShaderParameters() override;

		virtual void Init();
		virtual void Uninit(){}

		virtual void Update();
		virtual void Reset(){}

		void SetXY(float x, float y);
		void SetScaleXY(float x, float y);
		void SetRelativeXY(float x, float y);
		void SetRelativeScaleXY(float x, float y);

		virtual GamePlayObjectType Intersect(GamePlayObject* gameplayObject, CharacterState* state = NULL){return GamePlayObjectType_Invalid;}

		virtual const GamePlayObjectType GetGameplayObjectType()const =0{return GamePlayObjectType_Invalid;}

		virtual TextureId GetTextureID()=0{return -1;}
		virtual MaterialID GetMaterialID()=0{return -1;}

		static ShaderListID GetShaderID();
		static GeometryID GetQuadID();

		const glm::vec4 GetPosition()const{return m_currentPosition;}
		const glm::vec4 GetScale()const{return m_scale;}

	    virtual glm::vec4 GetNextPosition()const{return m_currentPosition;}

		virtual CharacterState GetCharacterState(){return Normal;}

	protected:
		bool m_isPositionAffectedByLevel;
		glm::vec4 m_currentPosition;
		glm::vec4 m_scale;

		static float ms_cameraY;
	};

} // namespace SceneManager
} // namespace Atum


#endif
