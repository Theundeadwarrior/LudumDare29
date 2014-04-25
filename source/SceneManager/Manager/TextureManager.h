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

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

    // Get Texture from id
    TextureId CreateTexture(const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format);
    TextureId CreateTextureSkyBox(const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format);
	void RemoveTexture (TextureId textureID);
    LowLevelGraphics::Texture* const GetTexture( TextureId textureID );
	LowLevelGraphics::TextureSkyBox* const GetSkyBox( TextureId textureID );
	void ClearAll();

private:
    TextureId InsertTexture( LowLevelGraphics::Texture* const texture );
	TextureId InsertTextureSkyBox( LowLevelGraphics::TextureSkyBox* const textureSkyBox );

    TextureManager(TextureManager const&);
    void operator=(TextureManager const&);

    TextureMap m_textureMap;
	TextureSkyBoxMap m_textureSkyBoxMap;
};

}
}

#endif