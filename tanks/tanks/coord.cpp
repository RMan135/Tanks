//coming soon

#include "coord.h"

#define TILE_WIDTH 24
#define TILE_HEIGHT 24
 
void coordToDouble(position& pos){ // converteste coordonatele la double
	if(pos.type == coordType_double)
		return;
	pos.x.doubleVal = (double)pos.x.longVal / TILE_WIDTH;
	pos.y.doubleVal = (double)pos.y.longVal / TILE_HEIGHT;
	pos.type = coordType_double;
}

void coordToLong(position& pos){ // converteste coordonatele la long
	if(pos.type == coordType_long)
		return;
	pos.x.longVal = (long)(pos.x.doubleVal * TILE_WIDTH) + (long)((pos.x.doubleVal - (long)pos.x.doubleVal) * 2);
	pos.y.longVal = (long)(pos.y.doubleVal * TILE_HEIGHT) + (long)((pos.y.doubleVal - (long)pos.y.doubleVal) * 2);
	pos.type = coordType_long;
}

