#ifndef LOWLEVELGRAPHICS_MATERIAL_TEXTURESKYBOX_H
#define LOWLEVELGRAPHICS_MATERIAL_TEXTURESKYBOX_H

#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"

namespace Atum
{
namespace LowLevelGraphics
{

class TextureSkyBox
{
public:
	// The order for the images must be left, right, bottom, top, front and back
    TextureSkyBox(const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format);
    ~TextureSkyBox();

    unsigned int GetID(){return m_id;}
private:
    unsigned int m_id;
};

}
}

#endif