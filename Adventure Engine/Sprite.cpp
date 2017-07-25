#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

Sprite::Sprite()
{
	m_vboID = 0;
}


Sprite::~Sprite()
{
	if (m_vboID == 0)
	{
		glDeleteBuffers(1, &m_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}
	
	Vertex vertexData[6];
	//first triangle
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	//set all color
	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 0;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;

	//bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,GL_STATIC_DRAW);

	//unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	//this is position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));

	//this is color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
