#ifndef SCENEMANAGER_MAINCHARACTER_H
#define SCENEMANAGER_MAINCHARACTER_H

#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{

	class MainCharacter : public GamePlayObject
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

		MainCharacter(MaterialID materialID, const Transform& transform);
		~MainCharacter();

		void GetPropertyList ( PropertyList& o_properties );
		void UpdatePropertyList ( PropertyList& i_properties );

		void Update();
		void Reset();

		virtual const GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::MainCharacter;}

	private:
		CharacterState m_currentState;
		glm::vec4 m_currentPosition;
		glm::vec4 m_colorBlend;
		float m_scale;
	};

} // namespace SceneManager
} // namespace Atum


#endif
