#ifndef TEXTURE_PROPERTY_T_H
#define TEXTURE_PROPERTY_T_H

#include <string>

#include "Property.h"

namespace Atum
{
namespace SceneManager
{
	
	class TextureProperty: public Property {

		public:
			TextureProperty( const std::string& textureTypeName, const std::string& texturePath );
			~TextureProperty();

	};

}
}

#endif //TEXTURE_PROPERTY_T_H