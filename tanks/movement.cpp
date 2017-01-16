#include "movement.h"
#include <cmath>

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

bool canMoveStraightAtoB(double x1, double y1, double x2, double y2, double x3, double y3,
                         short stepsSoFar, short nrSteps)
{
    if (stepsSoFar > nrSteps) return 1;

    return ((canReach[(short)x1][(short)y1] >= 2) &&
            (canReach[(short)x2][(short)y2] >= 2) &&
             canMoveStraightAtoB(x1, y1, (x1+x2)/2, (y1+y2)/2, x2, y2, stepsSoFar+1, nrSteps) &&
             canMoveStraightAtoB(x2, y2, (x2+x3)/2, (y2+y3)/2, x3, y3, stepsSoFar+1, nrSteps) );
}

bool canFireFromAtoB(double x1, double y1, double x2, double y2, double x3, double y3,
                         short stepsSoFar, short nrSteps)
{
    if (stepsSoFar > nrSteps) return 1;

    return ((!collisionMap.tiles[(short)x1][(short)y1]) &&
            (!collisionMap.tiles[(short)x2][(short)y2]) &&
             canFireFromAtoB(x1, y1, (x1+x2)/2, (y1+y2)/2, x2, y2, stepsSoFar+1, nrSteps) &&
             canFireFromAtoB(x2, y2, (x2+x3)/2, (y2+y3)/2, x3, y3, stepsSoFar+1, nrSteps) );
}

bool canMove(double x1, double y1, double x2, double y2)
{
    short dist, nrSteps = 1, nrIncrements = 1;
    dist = distance(x1, x2, y1, y2);

    while (nrIncrements <= dist)
    {
        nrSteps++;
        nrIncrements *= 2;
    }

    return canMoveStraightAtoB(x1, y1, (x1+x2)/2, (y1+y2)/2, x2, y2, 1, nrSteps);
}

bool canFire(double x1, double y1, double x2, double y2)
{
    short dist, nrSteps = 1, nrIncrements = 1;
    dist = distance(x1, x2, y1, y2);

    while (nrIncrements <= dist * 16)
    {
        nrSteps++;
        nrIncrements *= 2;
    }

    return canFireFromAtoB(x1, y1, (x1+x2)/2, (y1+y2)/2, x2, y2, 1, nrSteps);
}

void getClosestReachableTile (short &x, short &y)
{
    if (canReach[x][y] >= 2) return;

    short coordNextX[] = {0, 1, 0, -1, -1, -1, 1, 1},
          coordNextY[] = {1, 0, -1, 0, 1, -1, 1, -1};

    for (short k = 0; k < 8; ++k)
        if (canReach[x + coordNextX[k]][y + coordNextY[k]] >= 2)
        {
            x = x + coordNextX[k];
            y = y + coordNextY[k];
            break;
        }
}

short route(short x1, short y1, short x2, short y2, short movX[200], short movY[200], short &routeLength)
{
    bool reachedEnd = 0;
    short qEnd = 0, qPos = 0, k, i, j, length,
        coordNextX[] = {0, 1, 0, -1},
        coordNextY[] = {1, 0, -1, 0},
        steps[MAX_TILES_WIDTH][MAX_TILES_HEIGHT];

    short qi[1000], qj[1000];
	getClosestReachableTile(x2, y2);

    for (i = 0; i < collisionMap.width + 2; ++i)
        for (j = 0; j < collisionMap.height + 2; ++j)
            steps[i][j] = -1;

    qi[qPos] = x1;
    qj[qPos] = y1;
    steps[x1][y1] = 0;

    while (qPos <= qEnd)
    {
        for (k = 0; k < 4; ++k)
        {
            i = qi[qPos] + coordNextX[k];
            j = qj[qPos] + coordNextY[k];

            if (canReach[i][j] >= 2 && steps[i][j]==-1)
            {
                    qEnd++;
                    qi[qEnd] = i;
                    qj[qEnd] = j;
                    steps[i][j] = steps[qi[qPos]][qj[qPos]] + 1;

                if (i == x2 && j == y2)
                    {
                        reachedEnd = 1;
                        break;
                    }
            }
        }
        if (reachedEnd) break;
        qPos++;
    }

    length = steps[i][j];

    for (short l = length; l > 1; --l)
    {
        for (k = 0; k < 4; ++k)
            if (steps[i+coordNextX[k]][j+coordNextY[k]] == steps[i][j] - 1)
            {
                i = i+coordNextX[k];
                j = j+coordNextY[k];
                movX[l] = i;
                movY[l] = j;
                break;
            }
    }

    movX[1] = x1;
    movY[1] = y1;
    routeLength = length;   

    return 0;
}
