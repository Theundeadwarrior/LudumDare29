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
		enum Sprites
		{
			Sprites_Above,
			Sprites_Transition,
			Sprites_Count
		};

		MainCharacter();
		~MainCharacter();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		virtual void Init();
		virtual void Uninit();

		virtual void Update();
		void UpdateSprite();
		virtual void Reset();

		// Used when changing surface

		void GoBeneathTheSurface();

		virtual TextureId GetTextureID();
		virtual MaterialID GetMaterialID();

		std::vector<TextureId>* GetTextureIDList();

		virtual const GamePlayObject::GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::GamePlayObjectType_MainCharacter;}

		virtual GamePlayObject::GamePlayObjectType Intersect(GamePlayObject* gameplayObject, GamePlayObject::CharacterState* state = NULL) override;

		virtual void NotifyKeyPressed(const Events::KeyboardEvent& event);

		void Jump();

		float GetSpeed(){return m_speed;}

		virtual glm::vec4 GetNextPosition()const{return glm::vec4(m_currentPosition[0], m_currentPosition[1]+m_speed,0,0);}

		virtual CharacterState GetCharacterState(){ return m_currentState; }
		void SetCharacterState(CharacterState state){ m_currentState = state; }

		virtual void BindShaderParameters() override;

		const bool GetIsAtStartLevel()const{return m_isAtStartLevel;}
		void SetIsAtStartLevel(bool isAtStart){m_isAtStartLevel = isAtStart;}

	private:
		GamePlayObject::CharacterState m_currentState;
		glm::vec4 m_colorBlend;

		float m_speed;
		float m_cameraDiff;

		std::vector<TextureId> m_textureIdListPerState[Sprites_Count];
		std::vector<TextureId>::iterator m_currentSprite;
		Sprites m_currentSpriteState;

		bool m_isAtStartLevel;
	};

} // namespace SceneManager
} // namespace Atum


#endif
