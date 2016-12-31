#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#define MAX_TILES_WIDTH 32
#define MAX_TILES_HEIGHT 24

struct matrix
{
    bool tiles[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];
    short width, height;
};

matrix collision_map;

#include "terrainGeneration.h"

void selectMap()
{
    generateRandomMatrix(collision_map, 7);
    smoothenMatrix(collision_map, 3, 1, 1);
}

#endif
