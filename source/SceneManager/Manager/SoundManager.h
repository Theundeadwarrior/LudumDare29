#ifndef SCENEMANAGER_TEXTURE_MANAGER_H
#define SCENEMANAGER_TEXTURE_MANAGER_H

#include <map>
#include "SceneManager/Manager/TypedefID.h"
#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include "Utilities/Image/ImageUtilities.h"

namespace Atum
{
namespace LowLevelGraphics{class Texture;}
namespace LowLevelGraphics{class TextureSkyBox;}

namespace SceneManager
{
typedef std::map<TextureId, LowLevelGraphics::Texture*> TextureMap;
typedef std::map<TextureId, LowLevelGraphics::TextureSkyBox*> TextureSkyBoxMap;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

private:
    SoundManager(SoundManager const&);
};

}
}

#endif