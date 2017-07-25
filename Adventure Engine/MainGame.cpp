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
	m_maxFps = 120.0f;
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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//open sdl window
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

	//check open gl version
	printf("*** OpenGl version:%s ***\n",glGetString(GL_VERSION));

	glClearColor(0.0f,0.0f,1.0f,1.0f);

	//set VSYNC 1 on 0 off
	SDL_GL_SetSwapInterval(0);

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

void MainGame::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	
	float currentTicks;
	currentTicks = SDL_GetTicks();

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}

	

}

void MainGame::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		//used to frame time measuring
		float startTicks = SDL_GetTicks();

		processInput();

		m_time += 0.01f;

		drawGame();

		calculateFPS();

		//print only 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter > 10)
		{
			cout << m_fps << endl;
			frameCounter = 0;
		}

		//limit the max fps
		float frameTicks = SDL_GetTicks() - startTicks;
		if ((1000.0f / m_maxFps) > frameTicks)
		{
			SDL_Delay(1000.0f / m_maxFps - frameTicks);
		}
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
