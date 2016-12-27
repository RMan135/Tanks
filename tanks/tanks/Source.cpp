#include <SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650
#define FPS 60

struct Sprite
{
	SDL_Surface *sprite;

	void loadSprite(char path[])
	{
		sprite = SDL_LoadBMP(path);
	}

	void showSprite(SDL_Surface *dest, int x, int y)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		SDL_BlitSurface(sprite, NULL, dest, &rect);
	}

	void setAlpha(Uint32 color)
	{
		SDL_SetColorKey(sprite, SDL_TRUE, color);
	}
};

int main(int argc, char* args[])
{
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *WINDOW = NULL;

	WINDOW = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (WINDOW == NULL)
	{
		cout << "Window could not be initialized! " << endl << SDL_GetError();
	}

	SDL_Surface *SCREEN = SDL_GetWindowSurface(WINDOW);
	if (SCREEN == NULL)
	{
		cout << "Could not get window surface! " << endl << SDL_GetError();
	}

	Uint32 color_black = SDL_MapRGB(SCREEN->format, 0, 0, 0);
	Uint32 startingTick;

	///// TESTING GROUNDS /////
	
	Sprite s;
	s.loadSprite("media/tank.bmp");
	s.setAlpha(SDL_MapRGB(s.sprite->format, 255, 255, 255));
	int x, y;
	x = y = 0;

	///////////////////////////
	bool running = true;
	SDL_Event event;

	while(running)				// MAIN LOOP
	{
		// Get current tick (for fps cap)
		startingTick = SDL_GetTicks();

		// Make screen black
		SDL_FillRect(SCREEN, NULL, color_black);

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

		s.showSprite(SCREEN, (x++) % SCREEN_WIDTH, (y++) % SCREEN_HEIGHT);

		/////////////////////////

		// Update window
		SDL_UpdateWindowSurface(WINDOW);

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