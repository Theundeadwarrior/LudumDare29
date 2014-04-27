#ifndef SCENEMANAGER_MAINCHARACTER_H
#define SCENEMANAGER_MAINCHARACTER_H

#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"

#include "Events/EventManager.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{

	class MainCharacter : public GamePlayObject, public Events::InputKeyboardListener
	{
	public:
		MainCharacter();
		~MainCharacter();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		virtual void Init();
		virtual void Uninit();

		virtual void Update();
		virtual void Reset();

		virtual TextureId GetTextureID();
		virtual MaterialID GetMaterialID();

		virtual const GamePlayObject::GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::GamePlayObjectType_MainCharacter;}

		virtual GamePlayObject::GamePlayObjectType Intersect(GamePlayObject* gameplayObject, GamePlayObject::CharacterState* state = NULL) override;

		virtual void NotifyKeyPressed(const Events::KeyboardEvent& event);

		void Jump();

		float GetSpeed(){return m_speed;}

		virtual glm::vec4 GetNextPosition()const{return glm::vec4(m_currentPosition[0], m_currentPosition[1]+m_speed,0,0);}

	private:
		GamePlayObject::CharacterState m_currentState;
		glm::vec4 m_colorBlend;

		float m_acceleration;
		float m_speed;
	};

} // namespace SceneManager
} // namespace Atum


#endif
