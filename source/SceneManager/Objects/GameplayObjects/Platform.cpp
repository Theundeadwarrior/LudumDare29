#include "SceneManager/Objects/GameplayObjects/Platform.h"
#include "SceneManager/SceneManager.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "SceneManager/Level/Level.h"

namespace Atum
{
namespace SceneManager
{
	Platform::Platform(glm::vec4 position, glm::vec4 scale)
		: GamePlayObject(position, scale)
	{
	}

	const GamePlayObject::GamePlayObjectType Platform::GetGameplayObjectType() const
	{
		throw std::exception("The method or operation is not implemented.");
	}

	Atum::SceneManager::TextureId Platform::GetTextureID()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	Atum::SceneManager::MaterialID Platform::GetMaterialID()
	{
		throw std::exception("The method or operation is not implemented.");
	}

} // namespace SceneManager
} // namespace Atum
