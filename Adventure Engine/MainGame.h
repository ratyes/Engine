#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <vector>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "GLTexture.h"

enum class GameState {PLAY,EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();


	void run();



private:
	void initSystems();
	void initShaders();
	void processInput();

	void gameLoop();
	void drawGame();

	SDL_Window* m_window;
	char* m_screenTitle;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;

	vector<Sprite*> m_sprites;
	GLSLProgram m_colorProgram;

	float m_time;

};

