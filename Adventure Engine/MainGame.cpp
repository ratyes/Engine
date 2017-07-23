#include "MainGame.h"

#include <iostream>
#include <string>

using namespace std;

void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Enter any key to quit..." << endl;
	int tmp;
	cin >> tmp;
	SDL_Quit();
}

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

	if (m_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContex = SDL_GL_CreateContext(m_window);
	if (glContex == nullptr)
	{
		fatalError("SDL_GL contex could not be created!");
	}


	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("could not initailize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f,0.0f,1.0f,1.0f);

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
		drawGame();
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnableClientState(GL_COLOR_ARRAY);


	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);
	glEnd();


	SDL_GL_SwapWindow(m_window);
}
