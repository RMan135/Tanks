#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Texture.h"
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650
#define FPS 60



int main(int argc, char* args[])
{
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *WINDOW = NULL;

	WINDOW = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (WINDOW == NULL)
	{
		cout << "Window could not be initialized! " << endl << SDL_GetError();
	}

	SDL_Renderer *RENDER_TARGET = NULL;
	RENDER_TARGET = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	if (RENDER_TARGET == NULL)
	{
		cout << "Renderer could not be created! " << endl << SDL_GetError();
	}

	Uint32 startingTick;

	///// TESTING GROUNDS /////
	
	Texture t;
	t.setRenderTarget(RENDER_TARGET);
	t.loadTexture("media/block.png");

	///////////////////////////
	bool running = true;
	SDL_Event event;

	while(running)				// MAIN LOOP
	{
		// Get current tick (for fps cap)
		startingTick = SDL_GetTicks();

		// Make screen black
		SDL_SetRenderDrawColor(RENDER_TARGET, 0, 0, 0, 0);
		SDL_RenderClear(RENDER_TARGET);

		// Handle events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}

		}
		//// TESTING GROUNDS ////

		t.simpleRender(150, 300);

		/////////////////////////

		// Update window
		SDL_RenderPresent(RENDER_TARGET);

		// Cap the fps
		if ((1000 / FPS) > SDL_GetTicks() - startingTick)
		{
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
		}
	}

	SDL_DestroyWindow(WINDOW);
	SDL_Quit();
	return 0;
}