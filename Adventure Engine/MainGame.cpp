#include <iostream>
#include "MainGame.h"



MainGame::MainGame()
{
	m_window = nullptr;
	m_screenTitle = "Adventure Engine";
	m_screenWidth = 1024;
	m_screenHeight = 768;
	m_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}
void MainGame::initSystems()
{
	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow(m_screenTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << std::endl;;
			std::cout << evnt.motion.y << std::endl;;
			break;
		}
	}
}

void MainGame::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		processInput();
	}
}