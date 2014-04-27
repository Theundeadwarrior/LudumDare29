#ifndef SCENEMANAGER_PLATFORM_H
#define SCENEMANAGER_PLATFORM_H

#include "SceneManager/Objects/Object.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"

namespace Atum
{
namespace SceneManager
{
	class Platform : public GamePlayObject
	{
	public:
		enum IntersectionResult
		{
			IntersectionResult_Top,
			IntersectionResult_Left,
			IntersectionResult_None
		};

		Platform::Platform(glm::vec4 position, glm::vec4 scale);
		~Platform() {}

		virtual const GamePlayObjectType GetGameplayObjectType() const override;

		virtual TextureId GetTextureID() override;

		virtual MaterialID GetMaterialID() override; 

		virtual void Init();

		virtual void Uninit();

		virtual GamePlayObject::GamePlayObjectType Intersect(GamePlayObject* gameplayObject, GamePlayObject::CharacterState* state = NULL) override;

		IntersectionResult IntersectMainCharacter(GamePlayObject* gameplayObject);
		IntersectionResult IntersectMainCharacterWithPosition(const glm::vec4& position, const glm::vec4& scale, bool upperBound);
	};
} // namespace SceneManager
} // namespace Atum


#endif
