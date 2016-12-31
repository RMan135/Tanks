#ifndef TERRAIN_GENERATION_HEADER
#define TERRAIN_GENERATION_HEADER

#include <stdlib.h>
#include <time.h>

void copyMatrix(bool matCopy[MAX_TILES_WIDTH][MAX_TILES_HEIGHT], matrix mat)
{
    for (int i = 0; i <= mat.width + 1; ++i)
        for (int j = 0; j <= mat.height + 1; ++j)
            matCopy[i][j] = mat.tiles[i][j];
}

void generateRandomMatrix (matrix &mat, short placementChance)
{
    srand (time(NULL));

    //mat.height = rand() % (MAX_TILES_HEIGHT - 2 - 10) + 10;
    //mat.width = rand() % (MAX_TILES_WIDTH - 2 - 14) + 14;
    mat.height = MAX_TILES_HEIGHT -2;
    mat.width = MAX_TILES_WIDTH -2;

    //if (mat.height < 10) mat.height = 10;
    //if (mat.width < 14) mat.width = 14;
    //mat.height -= mat.height % 2;
    //mat.width -= mat.width % 2;

    for (int i = 0; i <= mat.width + 1; ++i) mat.tiles[i][0] = mat.tiles[i][mat.height+1] = 1;
    for (int i = 1; i <= mat.height + 1; ++i) mat.tiles[0][i] = mat.tiles[mat.width+1][i] = 1;

    for (short i = 1; i <= mat.width; ++i)
        for (short j = 1; j <= mat.height; ++j)
            mat.tiles[i][j] = ( (rand() % 100) < placementChance );
}

void smoothenMatrix (matrix &playingField, short emptyLimit, short occupiedLimit, short smoothenFactor)
{
    short i, j, k, l,
          neighbourX[] = {1, 1, 0, -1, -1, -1, 0, 1},
          neighbourY[] = {0, 1, 1, 1, 0, -1, -1, -1},
          numberOfNeighbours;

    bool oldPlayingField[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];

    for (l = 1; l <= smoothenFactor; ++l)
    {
        copyMatrix (oldPlayingField, playingField);

        for (i = 1; i <= playingField.width; ++i)
            for (j = 1; j <= playingField.height; ++j)
            {
                numberOfNeighbours = 0;
                for (k = 0; k < 8; ++k) numberOfNeighbours += oldPlayingField[i + neighbourX[k]][j + neighbourY[k]];

                if (oldPlayingField[i][j])
                {
                    if (numberOfNeighbours < emptyLimit)
                        playingField.tiles[i][j] = 0;
                }
                else
                {
                    if (numberOfNeighbours > occupiedLimit)
                        playingField.tiles[i][j] = 1;
                }
            }
    }
}

void DFS()
{

}

#endif
