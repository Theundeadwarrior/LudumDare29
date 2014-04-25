#include "SceneManager/Manager/TextureManager.h"

#include "LowLevelGraphics/Material/Texture/Texture.h"
#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"
#include "Utilities/IdGenerator/IdGenerator.h"

namespace Atum
{
namespace SceneManager
{

//-----------------------------------------------------------------------------
TextureManager::TextureManager()
{
}

//-----------------------------------------------------------------------------
TextureManager::~TextureManager()
{
	ClearAll();
}

//-----------------------------------------------------------------------------
TextureId TextureManager::CreateTexture(const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format)
{
    LowLevelGraphics::Texture* texture = new LowLevelGraphics::Texture(imageParameters, format);
    return InsertTexture(texture);
}

TextureId TextureManager::CreateTextureSkyBox(const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const LowLevelGraphics::LowLevelAPI::TextureFormat& format)
{
	LowLevelGraphics::TextureSkyBox* texture = new LowLevelGraphics::TextureSkyBox(imageParameters, format);
	return InsertTextureSkyBox(texture);
}

//-----------------------------------------------------------------------------
void TextureManager::RemoveTexture (TextureId textureID)
{
    TextureMap::iterator it (m_textureMap.find(textureID));
    if (it != m_textureMap.end()) //id exists!
    {
        delete (*it).second;
        m_textureMap.erase(it);
    }
}

//-----------------------------------------------------------------------------
LowLevelGraphics::Texture* const TextureManager::GetTexture(TextureId textureID)
{
    if (m_textureMap.find(textureID) != m_textureMap.end()) //id exists!
    {
        return m_textureMap[textureID];
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------
LowLevelGraphics::TextureSkyBox* const TextureManager::GetSkyBox(TextureId textureId)
{
	if (m_textureSkyBoxMap.find(textureId) != m_textureSkyBoxMap.end()) //id exists!
	{
		return m_textureSkyBoxMap[textureId];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
TextureId TextureManager::InsertTexture(LowLevelGraphics::Texture* const texture)
{
    TextureId id = Utilities::IdGenerator::GetInstance().GenerateId();
    m_textureMap[id] = texture;
    return id;
}

//-----------------------------------------------------------------------------
TextureId TextureManager::InsertTextureSkyBox(LowLevelGraphics::TextureSkyBox* const textureSkyBox)
{
	TextureId id = Utilities::IdGenerator::GetInstance().GenerateId();
	m_textureSkyBoxMap[id] = textureSkyBox;
	return id;
}

void TextureManager::ClearAll()
{
	TextureMap::iterator it(m_textureMap.begin());
	for(; it != m_textureMap.end(); it++)
	{
		delete (*it).second;
	}
	TextureSkyBoxMap::iterator itSkybox(m_textureSkyBoxMap.begin());
	for(; itSkybox != m_textureSkyBoxMap.end(); itSkybox++)
	{
		delete (*itSkybox).second;
	}
	m_textureMap.clear();
	m_textureSkyBoxMap.clear();
}

}
}
