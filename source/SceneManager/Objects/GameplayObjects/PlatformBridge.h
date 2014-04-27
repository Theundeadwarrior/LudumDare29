#ifndef SCENEMANAGER_PLATFORMBRIDGE_H
#define SCENEMANAGER_PLATFORMBRIDGE_H

#include "SceneManager/Objects/Object.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/Platform.h"
#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"

namespace Atum
{
namespace SceneManager
{
	class PlatformBridge : public Platform
	{
	public:
		PlatformBridge::PlatformBridge(glm::vec4 position, glm::vec4 scale);
		~PlatformBridge() {}

		//virtual const GamePlayObjectType GetGameplayObjectType() const override;

		virtual const GamePlayObject::GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::GamePlayObjectType_Platform;}

		virtual TextureId GetTextureID() override;

		virtual MaterialID GetMaterialID() override; 

		virtual void Init();

		virtual void Uninit();

	};
} // namespace SceneManager
} // namespace Atum


#endif // SCENEMANAGER_PLATFORMBRIDGE_H
