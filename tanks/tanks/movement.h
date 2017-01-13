#ifndef MOVEMENT_HEADER
#define MOVEMENT_HEADER

#include "terrain.h"

double distance(double x1, double y1, double x2, double y2);

bool canMoveStraightAtoB(double x1, double y1, double x2, double y2, double x3, double y3,
                         short stepsSoFar, short nrSteps);

bool canFireFromAtoB(double x1, double y1, double x2, double y2, double x3, double y3,
                         short stepsSoFar, short nrSteps);

bool canMove(double x1, double y1, double x2, double y2);
bool canFire(double x1, double y1, double x2, double y2);

short route(short x1, short y1, short x2, short y2, short movX[200], short movY[200]);



#endif
