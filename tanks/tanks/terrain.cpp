#include "terrain.h"
#include "terrainGeneration.h"
ifstream fin;

matrix collisionMap;
matrix accessibleTiles;
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
