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
bool pause = false;
void changeGameState(int newGameState);
int numberOfHumans = 1;
int numberOfEnemies = 1;
int difficulty = 1;

void addHuman();
void addEnemy();
void removeHuman();
void removeEnemy();
void increaseDifficulty();
void decreaseDifficulty();

Uint32 startingTick;

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDER_TARGET = NULL;

bool running = true;

Tileset currentTileset;

void handleEvents();

SDL_Event e;
int mouseX, mouseY;
bool mouseDown = false;

Texture t;
int angle = 0;

void previewMap(int x, int y, int scale);
void nextMap();
void randomMap();
void showMap();

void init();
void displayNumber(int x, int y, int n, int scale);
void displayDifficulty(int x, int y, int n, int scale);

int currentMap = -1;

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
	nextMap();

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
		{
			showMap();
		}

		// show tanks here

		if(gameState == GAME_SETUP || gameState == MAP_SELECTION || gameState == GENERATE || gameState == LOAD)
			previewMap(SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 4, 12);
		menus[gameState].show();

		if (gameState == GAME_SETUP)
		{
			displayNumber(138, 170, numberOfHumans, 12);
			displayNumber(138, 202, numberOfEnemies, 12);
			displayDifficulty(138, 234, difficulty, 12);
		}

		cout << mouseX/24 << " " << mouseY/24 << endl;

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
		if (e.type == SDL_MOUSEBUTTONDOWN && mouseDown == false)
		{
			mouseDown = true;
			int k;
			for (k = 0; k < menus[gameState].getNumberOfButtons(); k++)
			{
				if (menus[gameState].getButtons()[k].pointIsInside(mouseX, mouseY))
				{
					if (menus[gameState].getButtons()[k].isJob("change_state"))
					{
						changeGameState(menus[gameState].getButtons()[k].getJobAux());
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("quit"))
					{
						running = false;
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("rand_map"))
					{
						randomMap();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("next_map"))
					{
						nextMap();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("add_human"))
					{
						addHuman();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("add_enemy"))
					{
						addEnemy();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("remove_human"))
					{
						removeHuman();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("remove_enemy"))
					{
						removeEnemy();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("inc_dif"))
					{
						increaseDifficulty();
						break;
					}
					if (menus[gameState].getButtons()[k].isJob("dec_dif"))
					{
						decreaseDifficulty();
						break;
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			mouseDown = false;
		}
	}
}

void previewMap(int x, int y, int scale)
{
	for (int i = 0; i <= collisionMap.width + 1; i++)
		for (int j = 0; j <= collisionMap.height + 1; j++)
			if (collisionMap.tiles[i][j] == 1)
			{
				SDL_SetRenderDrawColor(RENDER_TARGET, 0, 128, 0, 255);
				SDL_Rect renderSpace = { x + i * scale, y + j * scale, scale, scale };
				SDL_RenderDrawRect(RENDER_TARGET, &renderSpace);
				SDL_RenderDrawLine(RENDER_TARGET, x + i*scale, y + j*scale, x + i*scale + scale, y + j*scale + scale);
				SDL_RenderDrawLine(RENDER_TARGET, x + i*scale + scale, y + j*scale, x + i*scale, y + j*scale + scale);
			}
			else
			{
				if (isSpawnPoint[i][j] == 1)
					SDL_SetRenderDrawColor(RENDER_TARGET, 255, 255, 0, 255);
				else
					SDL_SetRenderDrawColor(RENDER_TARGET, 0, 32, 0, 255);
				SDL_Rect renderSpace = { x + i * scale, y + j * scale, scale, scale };
				SDL_RenderDrawRect(RENDER_TARGET, &renderSpace);
				SDL_RenderDrawLine(RENDER_TARGET, x + i*scale, y + j*scale, x + i*scale + scale, y + j*scale + scale);
				SDL_RenderDrawLine(RENDER_TARGET, x + i*scale + scale, y + j*scale, x + i*scale, y + j*scale + scale);
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
	{
		cout << "Changed game state to " << (State)newGameState << endl;
		gameState = (State)newGameState;
	}
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
		currentTileset.loadTileset("ruins", RENDER_TARGET);
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
		currentTileset.loadTileset("ruins", RENDER_TARGET);
		break;
	case 3:
		currentTileset.loadTileset("desert", RENDER_TARGET);
		break;
	}
}

void addHuman()
{
	if (numberOfHumans + numberOfEnemies < 4 && numberOfHumans < 2)
		numberOfHumans++;
	else
		cout << '\a';
}

void addEnemy()
{
	if (numberOfHumans + numberOfEnemies < 4)
		numberOfEnemies++;
	else
		cout << '\a';
}

void removeHuman()
{
	if (numberOfHumans > 1)
		numberOfHumans--;
	else
		cout << '\a';
}

void removeEnemy()
{
	if (numberOfEnemies + numberOfHumans - 1 >= 2)
		numberOfEnemies--;
	else
		cout << '\a';

}

void increaseDifficulty()
{
	if (difficulty < 3)
		difficulty++;
	else
		cout << '\a';
}

void decreaseDifficulty()
{
	if (difficulty > 1)
		difficulty--;
	else
		cout << '\a';
}

void displayNumber(int x, int y, int n, int scale)
{
	SDL_SetRenderDrawColor(RENDER_TARGET, 255, 255, 255, 255);
	int i;
	for (i = 0; i < n; i++)
	{
		SDL_RenderDrawLine(RENDER_TARGET, x + (i * scale/n), y, x + (i * scale/n), y + scale);
	}
}

void displayDifficulty(int x, int y, int n, int scale)
{
	switch (difficulty)
	{
	case 1:
		SDL_SetRenderDrawColor(RENDER_TARGET, 255, 255, 0, 255);
		break;
	case 2:
		SDL_SetRenderDrawColor(RENDER_TARGET, 255, 128, 0, 255);
		break;
	case 3:
		SDL_SetRenderDrawColor(RENDER_TARGET, 255, 0, 0, 255);
	}
	int i;
	for (i = 0; i < n; i++)
	{
		SDL_RenderDrawLine(RENDER_TARGET, x , y + (i*scale/4) + scale/4, x + scale/2, y + i*scale/4);
		SDL_RenderDrawLine(RENDER_TARGET, x + scale/2, y + (i*scale / 4) , x + scale, y + i*scale / 4 + scale/4);
	}
}

