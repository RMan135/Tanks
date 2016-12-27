#include <SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

	Uint32 blackColor = SDL_MapRGB(SCREEN->format, 0, 0, 0);
	SDL_FillRect(SCREEN, NULL, blackColor);
	SDL_UpdateWindowSurface(WINDOW);

	bool running = true;
	SDL_Event event;
	while(running)		//Main Loop
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(WINDOW);
	SDL_Quit();
	return 0;
}