#ifndef LOWLEVELGRAPHICS_MATERIAL_TEXTURE_H
#define LOWLEVELGRAPHICS_MATERIAL_TEXTURE_H

#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include "Utilities/Image/ImageUtilities.h"
#include <string>

namespace Atum
{
namespace LowLevelGraphics
{

class Texture
{
public:
    Texture(const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const LowLevelAPI::TextureFormat& format);
    ~Texture();

    unsigned int GetID(){return m_id;}
	std::string GetPath(){return m_path;}
private:
	std::string m_path;
    unsigned int m_id;
};

}
}

#endif