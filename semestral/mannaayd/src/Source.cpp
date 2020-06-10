#define SDL_MAIN_HANDLED 
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>  
#include <fstream>
#include <string>


using namespace std;



int main()
{
	const int FPS = 40;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	srand(static_cast<unsigned int>(time(NULL)));
	shared_ptr<Game> game = make_shared<Game>("Ant Wars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);

	while (game->inmenu())
	{
		frameStart = SDL_GetTicks();
		game->handleEventsmenu();
		game->updatemenu();
		game->rendermenu();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}
	game->init();
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->clean();

	return 0;
}
