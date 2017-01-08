#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Texture.h"
#include "terrain.h"
#include "terrainGeneration.h"
#include "Tileset.h"
using namespace std;

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 576
#define FPS 60

Uint32 startingTick;

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDER_TARGET = NULL;

bool running = true;

SDL_Event event;

Tileset currentTileset;

int main(int argc, char* args[])
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	WINDOW = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (WINDOW == NULL)
	{
		cout << "Window could not be initialized! " << endl << SDL_GetError();
		running = false;
	}
		
	RENDER_TARGET = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	if (RENDER_TARGET == NULL)
	{
		cout << "Renderer could not be created! " << endl << SDL_GetError();
		running = false;
	}

	currentTileset.loadTileset("desert", RENDER_TARGET);
	selectMap(4);

	while(running)
	{
		// Get current tick (for fps cap)
		startingTick = SDL_GetTicks();

		// Clear screen
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
		
		for (int i = 0; i <= collisionMap.width + 1; i++)
			for (int j = 0; j <= collisionMap.height + 1; j++)
				if (collisionMap.tiles[i][j] == 1)
					currentTileset.wall.simpleRender(i * 24, j * 24);
				else
					currentTileset.ground.simpleRender(i * 24, j * 24);


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