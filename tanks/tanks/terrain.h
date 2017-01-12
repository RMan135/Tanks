#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#define MAX_TILES_WIDTH 32
#define MAX_TILES_HEIGHT 24
#define NUMBER_OF_PRESET_MAPS 4

using namespace std;

#include <fstream>
#include "coord.h"

struct matrix
{
    short tiles[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];
    short width, height;
};

extern matrix collisionMap;
extern matrix accessibleTiles;
extern short isSpawnPoint[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];

extern short mapTheme,
             noOfPlayers;

/*
0 - empty
1 - wall
2 - accessible
3 - spawn point nearby
*/

extern coords playerSpawners[4];
extern coords powerupSpawners[4];

void getMap();

void selectMap(short choice);

void generateMap();

#endif
