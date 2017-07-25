#include "MainGame.h"
#include "Error.h"
#include <iostream>

using namespace std;



MainGame::MainGame()
{
	m_window = nullptr;
	m_screenTitle = "Adventure Engine";
	m_screenWidth = 1024;
	m_screenHeight = 768;
	m_gameState = GameState::PLAY;
	m_time = 0;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	m_sprites.push_back(new Sprite());
	m_sprites.back()->init(-1, -1, 1, 1, "textures/PNG/CharacterLeft_Walk1.png");

	m_sprites.push_back(new Sprite());
	m_sprites.back()->init(0.0f, -1, 1, 1, "textures/PNG/CharacterLeft_Walk1.png");


	m_sprites.push_back(new Sprite());
	m_sprites.back()->init(-1.0f, 0.0f, 1, 1, "textures/PNG/CharacterLeft_Walk1.png");
	


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

	//set up our opengl context
	SDL_GLContext glContex = SDL_GL_CreateContext(m_window);
	if (glContex == nullptr)
	{
		fatalError("SDL_GL contex could not be created!");
	}

	//set up glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("could not initailize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f,0.0f,1.0f,1.0f);

	initShaders();

}

void MainGame::initShaders()
{
	m_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertextUV");
	m_colorProgram.linkShaders();
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
			//std::cout << evnt.motion.x << std::endl;;
			//std::cout << evnt.motion.y << std::endl;;
			break;
		}
	}
}

void MainGame::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		processInput();

		m_time += 0.01f;

		drawGame();
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint texturelocation = m_colorProgram.getUniformLocation("mySampler");
	glUniform1i(texturelocation,0);

	GLint timeLocation = m_colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, m_time);

	for (int i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i]->draw();
	}


	glBindTexture(GL_TEXTURE_2D, 0);
	m_colorProgram.unUse();

	SDL_GL_SwapWindow(m_window);
}
