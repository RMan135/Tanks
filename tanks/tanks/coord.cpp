#include "coord.h"
#include "tank.h"

#define TILE_WIDTH 24
#define TILE_HEIGHT 24
 
void coordToDouble(coords& pos){ // converteste coordonatele la double
	pos.x.doubleVal = (double)pos.x.longVal / TILE_WIDTH;
	pos.y.doubleVal = (double)pos.y.longVal / TILE_HEIGHT;
	pos.type = coordType_double;
}

void coordToLong(coords& pos){ // converteste coordonatele la long
	pos.x.longVal = (long)pos.x.doubleVal * TILE_WIDTH;
	pos.y.longVal = (long)pos.y.doubleVal * TILE_HEIGHT;
	pos.type = coordType_long;
}

unsigned long long getLongX(tank* tank1){
	if (tank1->pos.type == coordType_long)
		return tank1->pos.x.longVal ;
	return (long)((tank1->pos.x.doubleVal - tank1->dim.x.doubleVal / 2) * TILE_WIDTH);
}

unsigned long long getLongY(tank* tank1) {
	if (tank1->pos.type == coordType_long)
		return tank1->pos.x.longVal;
	return (long)((tank1->pos.y.doubleVal - tank1->dim.y.doubleVal / 2) * TILE_HEIGHT);
}

