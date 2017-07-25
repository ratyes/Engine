#include "Error.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Enter any key to quit..." << endl;
	int tmp;
	cin >> tmp;
	SDL_Quit();
	exit(404);
}