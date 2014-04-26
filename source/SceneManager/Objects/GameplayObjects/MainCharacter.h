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
		enum CharacterState
		{
			Normal,
			Dead,
			Falling,
			Jumping,
			GhostSlowed,
			WindSlowed,
			WindSped
		};

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

		virtual const GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::MainCharacter;}

		virtual void NotifyKeyPressed(const Events::KeyboardEvent& event);

		void Jump();

	private:
		CharacterState m_currentState;
		glm::vec4 m_colorBlend;

		float m_acceleration;
		float m_speed;
	};

} // namespace SceneManager
} // namespace Atum


#endif
