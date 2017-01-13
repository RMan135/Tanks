#include "terrainGeneration.h"

void copyMatrix(matrix &matCopy, matrix mat)
{
    for (int i = 0; i <= mat.width + 1; ++i)
        for (int j = 0; j <= mat.height + 1; ++j)
            matCopy.tiles[i][j] = mat.tiles[i][j];

    matCopy.width = mat.width;
    matCopy.height = mat.height;
}

void clearMatrix(matrix &mat)
{
    for (short i = 1; i <= mat.width; ++i)
        for (short j = 1; j <= mat.height; ++j)
            mat.tiles[i][j] = 0;
}

void drawRectangle(matrix &mat, short x, short y, short width, short height, char value)
{
    for (short i = x; i < x + width; ++i) mat.tiles[i][y] = mat.tiles[i][y + height - 1] = value;
    for (short i = y + 1; i < y + height - 1; ++i) mat.tiles[x][i] = mat.tiles[x + width - 1][i] = value;
}

void generateRandomMatrix (matrix &mat, short placementChance)
{
    srand (time(NULL));

    mat.height = MAX_TILES_HEIGHT -2;
    mat.width = MAX_TILES_WIDTH -2;

    drawRectangle (mat, 0, 0, mat.width + 2, mat.height + 2, 1);

    clearMatrix(mat);

    for (short i = 1; i <= mat.width; ++i)
        for (short j = 1; j <= mat.height; ++j)
            mat.tiles[i][j] = ( (rand() % 100) < placementChance );
}

void smoothenMatrix (matrix &playingField, short emptyLimit, short occupiedLimit, short smoothness)
{
    short i, j, k, l,
          neighbourX[] = {1, 1, 0, -1, -1, -1, 0, 1},
          neighbourY[] = {0, 1, 1, 1, 0, -1, -1, -1},
          numberOfNeighbours;

    matrix oldPlayingField;

    for (l = 1; l <= smoothness; ++l)
    {
        copyMatrix (oldPlayingField, playingField);

        for (i = 1; i <= playingField.width; ++i)
            for (j = 1; j <= playingField.height; ++j)
            {
                numberOfNeighbours = 0;
                for (k = 0; k < 8; ++k)
                    numberOfNeighbours += oldPlayingField.tiles[i + neighbourX[k]][j + neighbourY[k]];

                if (oldPlayingField.tiles[i][j])
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

    if (emptyLimit > occupiedLimit)
        drawRectangle (playingField, 1, 1, playingField.width, playingField.height, 0);
}

void DFS(matrix &mat, short x, short y)
{
    if (mat.tiles[x][y] == 0)
    {
        mat.tiles[x][y] = 2;

        if ( !( (mat.tiles[x+1][y+1] == 1 && mat.tiles[x-1][y-1] == 1) ||
                (mat.tiles[x+1][y-1] == 1 && mat.tiles[x-1][y+1] == 1)    ) )
        {
            short cx1[] = {0, 1,  0, -1}, cy1[] = {1,  0, -1, 0},
                  cx2[] = {1, 1, -1, -1}, cy2[] = {1, -1, -1, 1},
                  cx3[] = {1, 0, -1,  0}, cy3[] = {0, -1,  0, 1};

            for (short k = 0; k < 4; ++k)
                if ( !mat.tiles[ x+cx1[k] ][ y+cy1[k] ]      &&
                      mat.tiles[ x+cx2[k] ][ y+cy2[k] ] != 1 &&
                      mat.tiles[ x+cx3[k] ][ y+cy3[k] ] != 1    )
                   {
                      DFS(mat, x+cx1[k], y+cy1[k]);
                      DFS(mat, x+cx2[k], y+cy2[k]);
                   }
    }
    }
}

bool isValidPlacement(matrix &mat, short x, short y, char badValue)
{
    if ( (mat.tiles[ x ][ y ] % 2 == badValue) ) return 0;
    if ( (mat.tiles[x-1][ y ] % 2 == badValue) ) return 0;
    if ( (mat.tiles[ x ][y-1] % 2 == badValue) ) return 0;
    if ( (mat.tiles[x-1][y-1] % 2 == badValue) ) return 0;
    return 1;
}

void generateRandomCoordinates(short &x, short &y, matrix mat)
{
    x = rand() % (mat.width - 3) + 2;
    y = rand() % (mat.height - 3) + 2;

    if (!isValidPlacement(mat, x, y, 1))
        generateRandomCoordinates(x, y, mat);
}

bool generateMapAndConfirm(short placementChance, short emptyLimit, short occupiedLimit, short smoothness, short noOfPlayers)
{
    srand (time(NULL));
    short x, y;

    generateRandomMatrix(collisionMap, placementChance);
    smoothenMatrix(collisionMap, emptyLimit, occupiedLimit, smoothness);
    copyMatrix(accessibleTiles, collisionMap);

    generateRandomCoordinates(x, y, collisionMap);
    DFS(accessibleTiles, x, y);
    //copyMatrix(canReach, accessibleTiles);

    for (int k = 0; k < noOfPlayers; ++k)
    {
        //generates player spawn point
        generateRandomCoordinates(x, y, accessibleTiles);
        if (!accessibleTiles.tiles[x][y]) return 0;

        drawRectangle(accessibleTiles, x, y, 2, 2, 3);
        drawRectangle(accessibleTiles, x-1, y-1, 4, 4, 3);
        playerSpawners[k].x.doubleVal = x;
        playerSpawners[k].y.doubleVal = y;

        //generates powerup spawn point
        generateRandomCoordinates(x, y, accessibleTiles);
        if (!accessibleTiles.tiles[x][y]) return 0;

        drawRectangle(accessibleTiles, x, y, 2, 2, 3);
        powerupSpawners[k].x.doubleVal = x;
        powerupSpawners[k].y.doubleVal = y;

    }

    return 1;
}

void generateMap()
{
 // placementChance | emptyLimit | occupiedLimit | smoothness
    short presets[4][4] = {{35, 4, 5, 1},  //forest
                           {30, 3, 4, 2},  //cave
                           {7 , 3, 1, 1},  //ruins
                           {3 , 0, 0, 0}}; //desert

    short pr;
    srand (time(NULL));
    pr = rand() % 4;
    mapTheme = pr;

    while ( !generateMapAndConfirm( presets[pr][0], presets[pr][1], presets[pr][2], presets[pr][3], noOfPlayers) );
}
