#ifndef TERRAIN_GENERATION_HEADER
#define TERRAIN_GENERATION_HEADER

#include <stdlib.h>
#include <time.h>
#include "terrain.h"

void copyMatrix(matrix &matCopy, matrix mat);

void clearMatrix(matrix &mat);

void drawRectangle(matrix &mat, short x, short y, short width, short height, char value);

void generateRandomMatrix (matrix &mat, short placementChance);

void smoothenMatrix (matrix &playingField, short emptyLimit, short occupiedLimit, short smoothness);

void DFS(matrix &mat, short x, short y);

bool isValidPlacement(matrix &mat, short x, short y, char badValue);

void generateRandomCoordinates(short &x, short &y, matrix mat);

bool generateMapAndConfirm(short placementChance, short emptyLimit, short occupiedLimit, short smoothness, short noOfPlayers);

void generateMap();

#endif
