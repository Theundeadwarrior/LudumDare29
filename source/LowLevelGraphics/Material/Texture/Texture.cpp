#include "LowLevelGraphics/Material/Texture/Texture.h"

namespace Atum
{
namespace LowLevelGraphics
{

Texture::Texture(const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const LowLevelAPI::TextureFormat& format)
{
    LowLevelAPI::GenerateTexture(m_id, imageParameters, format);
	m_path = imageParameters.path;
}

Texture::~Texture()
{
    LowLevelAPI::DeleteTexture(m_id);
}

}
}