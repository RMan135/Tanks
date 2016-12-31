#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#define MAX_TILES_WIDTH 32
#define MAX_TILES_HEIGHT 24

struct matrix
{
    char tiles[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];
    short width, height;
};

matrix collisionMap;
matrix accessibleTiles;
short theme;

/*
0 - empty
1 - wall
2 - accessible
3 - spawn point nearby
*/

/// mutati randurile 25-32 unde credeti ca e mai bine

struct coordinates
{
    double x, y;
};

coordinates playerSpawners[4];
coordinates powerupSpawners[4];

#include "terrainGeneration.h"

void selectMap()
{
    generateMap();
}

#endif
