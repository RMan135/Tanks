#ifndef TERRAIN_HEADER
#define TERRAIN_HEADER

#define MAX_TILES_WIDTH 32
#define MAX_TILES_HEIGHT 24
#define NUMBER_OF_PRESET_MAPS 4

using namespace std;

#include <fstream>
ifstream fin;

struct matrix
{
    short tiles[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];
    short width, height;
};

matrix collisionMap;
matrix accessibleTiles;
short mapTheme,
      noOfPlayers;

/*
0 - empty
1 - wall
2 - accessible
3 - spawn point nearby
*/

/// mutati randurile astea unde credeti ca e mai bine

struct coordinates
{
    double x, y;
};

coordinates playerSpawners[4];
coordinates powerupSpawners[4];

///

#include "terrainGeneration.h"

void getMap()
{
    fin >> mapTheme
        >> collisionMap.width
        >> collisionMap.height;

    for (int i = 0; i < 4; ++i)
        fin >> playerSpawners[i].x
            >> playerSpawners[i].y;

    for (int i = 0; i < 4; ++i)
        fin >> powerupSpawners[i].x
            >> powerupSpawners[i].y;

    for (int j = 0; j < collisionMap.height + 2; ++j)
            for (int i = 0; i < collisionMap.width + 2; ++i)
                fin >> collisionMap.tiles[i][j];

}

void selectMap(short choice)
{
    if (choice >= 0 && choice < NUMBER_OF_PRESET_MAPS)
    {
        switch (choice)
        {
            case 0 : { fin.open ("maps/forest1.dat");  break; }
            case 1 : { fin.open ("maps/cave1.dat");    break; }
            case 2 : { fin.open ("maps/ruins1.dat");   break; }
            case 3 : { fin.open ("maps/desert1.dat");  break; }
        }

        getMap();
        fin.close();
    }

    else
    generateMap();
}

#endif
