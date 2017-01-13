#include "terrain.h"
#include "terrainGeneration.h"
ifstream fin;

matrix collisionMap;
matrix accessibleTiles;
short canReach[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];
short isSpawnPoint[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];

short mapTheme,
      noOfPlayers = 4;

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

bool canEnlargeSquare(short x, short y, short length)
{
    for (short i = 0; i < length; ++i)
        if (collisionMap.tiles[x+length-1][y+i]) return 0;
    for (short i = 0; i < length-1; ++i)
        if (collisionMap.tiles[x+i][y+length-1]) return 0;
    return 1;
}

short getMaxFreeSquare(short x, short y)
{
    short k = 0;
    while (canEnlargeSquare(x, y, k+1))
        ++k;
    return k;
}

void getReachablePoints()
{
    for (short i = 1; i <= collisionMap.width; ++i )
        for (short j = 1; j <= collisionMap.height; ++j )
            canReach[i+1][j+1] = getMaxFreeSquare(i, j);
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
    getReachablePoints();

    /*
    for (int j = 0; j < collisionMap.height + 2; ++j)
       {
            for (int i = 0; i < collisionMap.width + 2; ++i)
            {
                if (canReach[i+1][j+1] >= 2) cout << "  ";
                if (canReach[i+1][j+1] == 1) cout << char(176) << char(176);
                if (canReach[i+1][j+1] == 0) cout << char(219) << char(219);
            }
            cout << endl;
       }
    */
}
