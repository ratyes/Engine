#include "TextureCach.h"
#include "ImageLoader.h"

#include <iostream>

TextureCach::TextureCach()
{
}


TextureCach::~TextureCach()
{
}

GLTexture TextureCach::getTexture(string filePath)
{
	//lookup in the map
	auto mit = m_textureMap.find(filePath);
	
	//check if not in the map
	if (mit == m_textureMap.end())
	{
		GLTexture texture = ImageLoader::loadPNG(filePath);

		//insert in map
		m_textureMap.insert(make_pair(filePath, texture));

		
		cout << "loaded texture \n";
		return texture;
	}
	cout << "loaded chached texture \n";
	
	return mit->second;
}
