#include "TextureProperty.h"

namespace Atum
{
namespace SceneManager
{

	TextureProperty::TextureProperty( const std::string& textureTypeName, const std::string& texturePath )
		: Property( textureTypeName, texturePath )
	{
		m_type = PROPERTY_TEXTURE;
	}

	TextureProperty::~TextureProperty()
	{}

}
}
