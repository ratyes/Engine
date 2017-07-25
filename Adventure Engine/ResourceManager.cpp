#include "ResourceManager.h"

TextureCach ResourceManager::m_textureCache;

GLTexture ResourceManager::getTexture(string texturePath)
{
	return m_textureCache.getTexture(texturePath);
}
