#pragma once
#include <map>
#include "GLTexture.h"

using namespace std;


class TextureCach
{
public:
	TextureCach();
	~TextureCach();

	GLTexture getTexture(string filePath);

private:
	map<string, GLTexture> m_textureMap;
};

