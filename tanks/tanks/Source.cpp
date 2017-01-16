#include <SDL.h>
#include <iostream>
#include "Texture.h"
#include "Tileset.h"
#include "Button.h"
#include "Menu.h"
#include "PowerUp.h"
#include "PlayerController.h"
#include "terrain.h"
#include "terrainGeneration.h"
#include "coord.h"
#include "tank.h"
#include "projectile.h"
using namespace std;

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 576
#define FPS 60
enum State
{
	MAIN_MENU = 0, GAME_SETUP = 1, PLAYING = 2, GAME_OVER = 3, MAP_SELECTION = 4, GENERATE = 5, LOAD = 6
};

Menu menus[7];

State gameState;
bool pause;
void changeGameState(int newGameState);
int numberOfHumans;
int numberOfEnemies;
int difficulty;

PlayerController pController[2];
int i;

Texture tankTexture, bullet, teamOverlay;
void spawnTanks();
int countAliveHumans();
int countAliveEnemies();
bool checkGameOver();
void generateHealthBarColor(int health, int &r, int &g, int &b);
void generateTeamColor(int team, int &r, int &g, int &b);


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

void previewMap(int x, int y, int scale);
void nextMap();
void randomMap();
void showMap();

void init();
void resetValues();
void displayNumber(int x, int y, int n, int scale);
void displayDifficulty(int x, int y, int n, int scale);

int currentMap;

int main(int argc, char* args[])
{
	init();
	resetValues();

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

	currentTileset.loadTileset("forest", RENDER_TARGET);
	tankTexture.setRenderTarget(RENDER_TARGET);
	tankTexture.loadTexture("media/tank.png");
	bullet.setRenderTarget(RENDER_TARGET);
	bullet.loadTexture("media/bullet.png");
	teamOverlay.setRenderTarget(RENDER_TARGET);
	teamOverlay.loadTexture("media/tank_team_overlay.png");
	

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
			if (checkGameOver())
			{
				SDL_Delay(3000);
				changeGameState(GAME_OVER);
			}
			updatePowerups();
			showMap();
			for (int i = 0; i < numberOfEnemies + numberOfHumans; i++)
			{
				if (tankVector[i] != NULL)
				{					
					if (i < numberOfHumans)
					{
						pController[i].update();
					}
					else
						act(tankVector[i], i);
					if (tankVector[i]->alive)
					{
						int r, g, b;
						generateHealthBarColor(tankVector[i]->health, r, g, b);
						SDL_Rect hpBar = { getLongX(tankVector[i]) - 3, getLongY(tankVector[i]) - 12, tankVector[i]->health / 3, 3 };
						SDL_SetRenderDrawColor(RENDER_TARGET, r, g, b, 255);

						tankTexture.render(getLongX(tankVector[i]), getLongY(tankVector[i]), tankVector[i]->rotation);
						SDL_RenderFillRect(RENDER_TARGET, &hpBar);

						generateTeamColor(tankVector[i]->team, r, g, b);
						teamOverlay.setColor(r, g, b);
						teamOverlay.render(getLongX(tankVector[i]), getLongY(tankVector[i]), tankVector[i]->rotation);
					}
					else
						destroyTank(tankVector[i]);
				}
				int j = 0;
				while (j < MAX_PROJECTILES_ONSCREEN) {
					if (tankVector[i] != nullptr && tankVector[i]->projOnScreen[j] != nullptr)
					{
						exist(tankVector[i]->projOnScreen[j]);
					}
					j++;
				}
				j = 0;
				while (j < MAX_PROJECTILES_ONSCREEN) {
					if (tankVector[i] != nullptr && tankVector[i]->projOnScreen[j] != nullptr)
					{
						bullet.render(getLongX(tankVector[i]->projOnScreen[j]) , getLongY(tankVector[i]->projOnScreen[j]) , tankVector[i]->projOnScreen[j]->rotation);
					}
					j++;
				}
			}
		}

		if(gameState == GAME_SETUP || gameState == MAP_SELECTION || gameState == GENERATE || gameState == LOAD)
			previewMap(SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 4, 12);
		menus[gameState].show();

		if (gameState == GAME_SETUP)
		{
			displayNumber(138, 170, numberOfHumans, 12);
			displayNumber(138, 202, numberOfEnemies, 12);
			displayDifficulty(138, 234, difficulty, 12);
		}


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

void resetValues()
{
	gameState = MAIN_MENU;
	pause = false;

	numberOfHumans = 1;
	numberOfEnemies = 1;
	difficulty = 1;
		
	int currentMap = 0;
	nextMap();
}

void handleEvents()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	int i;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running = false;
			break;
		}
		if (gameState == PLAYING && pause == false)
		{
			if (e.type == SDL_KEYDOWN)
			{
				for (i = 0; i < numberOfHumans; i++)
				{
					pController[i].keyDown(e.key.keysym.sym);
				}
			}
			if (e.type == SDL_KEYUP)
			{
				for (i = 0; i < numberOfHumans; i++)
				{
					pController[i].keyUp(e.key.keysym.sym);
				}
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
		if (gameState == GAME_OVER)
		{
			resetValues();
		}
		gameState = (State)newGameState;
		if(gameState == PLAYING)
		{
			spawnTanks();
			pause = false;
		}
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

void spawnTanks()
{
	int i;
	for (i = 0; i < numberOfHumans; i++)
	{
		tankVector[i] = createTank(general , i, playerSpawners[i].x.doubleVal - 0.5, playerSpawners[i].y.doubleVal - 0.5);
		pController[i].addTank(tankVector[i]);
		switch (i)
		{
		case 0:
			pController[i].setPlayerOne();
			break;
		case 1:
			pController[i].setPlayerTwo();
			break;
		}
	}
	for (i = numberOfHumans; i < numberOfEnemies + numberOfHumans; i++)
	{
		tankVector[i] = createTank(general, 2, playerSpawners[i].x.doubleVal -0.5, playerSpawners[i].y.doubleVal -0.5);
		addDiff(tankVector[i], difficulty);
		pController[i].ownedTank = NULL;
	}
	cout << "Spawned tanks." << endl;
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

int countAliveHumans()
{
	int i, num = 0;
	for (i = 0; i < numberOfHumans; i++)
	{
		if(tankVector[i] != nullptr)
			if (tankVector[i]->alive)
				num++;
	}
	return num;
}

int countAliveEnemies()
{
	int i, num = 0;
	for (i = numberOfHumans; i < numberOfEnemies + numberOfHumans; i++)
	{
		if (tankVector[i] != nullptr)
			if (tankVector[i]->alive)
				num++;
	}
	return num;
}

bool checkGameOver()
{
	if (numberOfHumans > 1)
	{
		if (numberOfEnemies == 0)
		{
			if (countAliveHumans() == 1)
				return 1;
		}
		else
		{
			if (countAliveHumans() == 1 && countAliveEnemies() == 0)
				return 1;
			if (countAliveHumans() == 0 && countAliveEnemies() > 0)
				return 1;
		}
	}
	else
	{
		if (countAliveEnemies() == 0)
			return 1;
		if (countAliveHumans() == 0)
			return 1;
	}
	return 0;
}

void generateHealthBarColor(int health, int &r, int &g, int &b)
{
	double red, green, blue;
	red = health;
	red = 511 - red * 5.11;
	if (red > 255) red = 255;
	if (red < 0) red = 0;
	green = health;
	green = green * 5.11;
	if (green > 255) green = 255;
	if (green < 0) green = 0;
	blue = health;
	blue = -100*10.23 + blue*10.23;
	if (blue > 255) blue = 255;
	if (blue < 0) blue = 0;
	r = red;
	g = green;
	b = blue;
}

void generateTeamColor(int team, int &r, int &g, int &b)
{
	switch (team)
	{
	case 0:
		r = 0;
		g = 255;
		b = 0;
		break;
	case 1:
		r = 64;
		g = 128;
		b = 255;
		break;
	case 2:
		r = 255;
		g = 0;
		b = 0;
		break;
	}
}