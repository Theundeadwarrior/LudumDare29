#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"

namespace Atum
{
namespace LowLevelGraphics
{

TextureSkyBox::TextureSkyBox(const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format)
{
    LowLevelAPI::GenerateTextureSkyBox(m_id, imageParameters, format);
}

TextureSkyBox::~TextureSkyBox()
{
    LowLevelAPI::DeleteTexture(m_id);
}

}
}