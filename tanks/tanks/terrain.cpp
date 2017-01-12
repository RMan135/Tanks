#include "terrain.h"
#include "terrainGeneration.h"
ifstream fin;

matrix collisionMap;
matrix accessibleTiles;
short isSpawnPoint[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];

short mapTheme,
      noOfPlayers;

coords playerSpawners[4];
coords powerupSpawners[4];

void getMap()
{
    fin >> mapTheme
        >> collisionMap.width
        >> collisionMap.height;

    for (int i = 0; i < 4; ++i)
        fin >> playerSpawners[i].x.doubleVal
            >> playerSpawners[i].y.doubleVal;

    for (int i = 0; i < 4; ++i)
        fin >> powerupSpawners[i].x.doubleVal
            >> powerupSpawners[i].y.doubleVal;

    for (int j = 0; j < collisionMap.height + 2; ++j)
            for (int i = 0; i < collisionMap.width + 2; ++i)
                fin >> collisionMap.tiles[i][j];

}

void createSpawnerMatrix(coords vec[4], short value)
{
    short x, y;

    for (int i = 0; i < 4; ++i)
	{
	    x = (short)vec[i].x.doubleVal;
          y = (short)vec[i].y.doubleVal;

	    isSpawnPoint[ x ][ y ] = value;
	    isSpawnPoint[x-1][ y ] = value;
          isSpawnPoint[ x ][y-1] = value;
          isSpawnPoint[x-1][y-1] = value;
	}
}

void clearSpawnerMatrix()
{
	for (int j = 0; j < collisionMap.height + 2; ++j)
		for (int i = 0; i < collisionMap.width + 2; ++i)
			isSpawnPoint[i][j] = 0;
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
	clearSpawnerMatrix();
    createSpawnerMatrix(playerSpawners, 1);
    createSpawnerMatrix(powerupSpawners, 2);
}
