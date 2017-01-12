#include <SDL.h>
#include <iostream>
#include "Texture.h"
#include "Tileset.h"
#include "Button.h"
#include "Menu.h"
#include "terrain.h"
#include "terrainGeneration.h"
#include "coord.h"
using namespace std;

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 576
#define FPS 60

enum State
{
	MAIN_MENU = 0, GAME_SETUP = 1, PLAYING = 2, GAME_OVER = 3, MAP_SELECTION = 4, GENERATE = 5, LOAD = 6
};

Menu menus[7];

State gameState = MAIN_MENU;
void changeGameState(int newGameState);

Uint32 startingTick;

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDER_TARGET = NULL;

bool running = true;

Tileset currentTileset;

void handleEvents();

SDL_Event e;
int mouseX, mouseY;

Texture t;
int angle = 0;

void previewMap(int x, int y, int scale);
void nextMap();
void randomMap();
void showMap();

void init();

int currentMap = 0;

int main(int argc, char* args[])
{
	init();

	int i;
	for (i = 0; i < 7; i++)
	{
		menus[i].setRenderTarget(RENDER_TARGET);
		switch (i)
		{
		case MAIN_MENU:
			menus[i].loadMenu("MAIN_MENU");
			break;
		case GAME_SETUP:
			menus[i].loadMenu("GAME_SETUP");
			break;
		case PLAYING:
			menus[i].loadMenu("PLAYING");
			break;
		case GAME_OVER:
			menus[i].loadMenu("GAME_OVER");
			break;
		case MAP_SELECTION:
			menus[i].loadMenu("MAP_SELECTION");
			break;
		case GENERATE:
			menus[i].loadMenu("GENERATE");
			break;
		case LOAD:
			menus[i].loadMenu("LOAD");
			break;
		}
	}

	currentTileset.loadTileset("cave", RENDER_TARGET);

	while (running)
	{
		// Get current tick (for fps cap)
		startingTick = SDL_GetTicks();

		// Clear screen
		SDL_SetRenderDrawColor(RENDER_TARGET, 0, 0, 0, 0);
		SDL_RenderClear(RENDER_TARGET);

		// Handle events
		handleEvents();
		if (gameState == PLAYING)
			showMap();
		else
			previewMap(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 12);
		menus[gameState].show();

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

void init()
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
}

void handleEvents()
{
	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running = false;
			break;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_w)
			{
				//move forwards
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				//move backwards
			}
			if (e.key.keysym.sym == SDLK_a)
			{
				//rotate left
			}
			if (e.key.keysym.sym == SDLK_d)
			{
				//rorate right
			}
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				randomMap();
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int k;
			for (k = 0; k < menus[gameState].getNumberOfButtons(); k++)
			{
				if (menus[gameState].getButtons()[k].pointIsInside(mouseX, mouseY))
				{
					if (menus[gameState].getButtons()[k].isJob("change_state"))
					{
						changeGameState(menus[gameState].getButtons()[k].getJobAux());
					}
					if (menus[gameState].getButtons()[k].isJob("quit"))
					{
						running = false;
					}
					if (menus[gameState].getButtons()[k].isJob("rand_map"))
					{
						randomMap();
					}
					if (menus[gameState].getButtons()[k].isJob("next_map"))
					{
						nextMap();
					}
				}
			}
		}
	}
}

void previewMap(int x, int y, int scale)
{
	for (int i = 0; i <= collisionMap.width + 1; i++)
		for (int j = 0; j <= collisionMap.height + 1; j++)
			if (collisionMap.tiles[i][j] == 1)
			{
				SDL_SetRenderDrawColor(RENDER_TARGET, 64, 64, 64, 255);
				SDL_Rect renderSpace = { x + i * scale, y + j * scale, scale, scale };
				SDL_RenderFillRect(RENDER_TARGET, &renderSpace);
			}
			else
			{
				if(isSpawnPoint[i][j] == 1)
					SDL_SetRenderDrawColor(RENDER_TARGET, 64, 128, 255, 255);
				else
					SDL_SetRenderDrawColor(RENDER_TARGET, 128, 128, 128, 255);
				SDL_Rect renderSpace = { x + i * scale, y + j * scale, scale, scale };
				SDL_RenderFillRect(RENDER_TARGET, &renderSpace);
			}
}

void showMap()
{
	for (int i = 0; i <= collisionMap.width + 1; i++)
		for (int j = 0; j <= collisionMap.height + 1; j++)
			if (collisionMap.tiles[i][j] == 1)
			{
				currentTileset.wall.simpleRender(i * 24, j * 24);
			}
			else
			{
				currentTileset.ground.simpleRender(i * 24, j * 24);
			}
}

void changeGameState(int newGameState)
{
	if (newGameState < 0 || newGameState > 6)
		cout << "Tried to change to invalid game state!" << endl;
	else
		gameState = (State)newGameState;
}

void nextMap()
{
	selectMap(currentMap++);
	switch (mapTheme)
	{
	case 0:
		currentTileset.loadTileset("forest", RENDER_TARGET);
		break;
	case 1:
		currentTileset.loadTileset("cave", RENDER_TARGET);
		break;
	case 2:
		currentTileset.loadTileset("desert", RENDER_TARGET);
		break;
	case 3:
		currentTileset.loadTileset("desert", RENDER_TARGET);
		break;
	}
	if (currentMap > 3)
		currentMap = 0;
}

void randomMap()
{
	selectMap(4);
	switch (mapTheme)
	{
	case 0:
		currentTileset.loadTileset("forest", RENDER_TARGET);
		break;
	case 1:
		currentTileset.loadTileset("cave", RENDER_TARGET);
		break;
	case 2:
		currentTileset.loadTileset("desert", RENDER_TARGET);
		break;
	case 3:
		currentTileset.loadTileset("desert", RENDER_TARGET);
		break;
	}
}