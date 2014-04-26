#ifndef SCENEMANAGER_PLATFORMCANYON_H
#define SCENEMANAGER_PLATFORMCANYON_H

#include "SceneManager/Objects/Object.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/Platform.h"
#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"

namespace Atum
{
namespace SceneManager
{
	class PlatformCanyon : public Platform
	{
	public:
		PlatformCanyon::PlatformCanyon(glm::vec4 position, glm::vec4 scale);
		~PlatformCanyon() {}

		//virtual const GamePlayObjectType GetGameplayObjectType() const override;

		virtual const GamePlayObject::GamePlayObjectType GetGameplayObjectType()const{return GamePlayObject::GamePlayObjectType_Platform;}

		virtual TextureId GetTextureID() override;

		virtual MaterialID GetMaterialID() override; 

		virtual void Init();

		virtual void Uninit();

	};
} // namespace SceneManager
} // namespace Atum


#endif // SCENEMANAGER_PLATFORMCANYON_H
