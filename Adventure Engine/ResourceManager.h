#pragma once
#include "TextureCach.h"

class ResourceManager
{
public:
	static GLTexture getTexture(string texturePath);


private:
	static TextureCach m_textureCache;
};

