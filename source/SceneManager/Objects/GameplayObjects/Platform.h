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
		Platform::Platform(glm::vec4 position, glm::vec4 scale);
		~Platform() {}

		virtual const GamePlayObjectType GetGameplayObjectType() const override;

		virtual TextureId GetTextureID() override;

		virtual MaterialID GetMaterialID() override; 

	};
} // namespace SceneManager
} // namespace Atum


#endif
