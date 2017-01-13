/*
	pentru manage-uit coordonate
*/

#ifndef COORD_HEADER
#define COORD_HEADER

struct tank;

union doublong{
	double doubleVal;
	long long longVal;
};

enum coordType {coordType_double, coordType_long};

struct coords{
	doublong x, y;
	coordType type;
};

void coordToDouble(coords& pos); // converteste coordonatele la double
void coordToLong(coords& pos); // converteste coordonatele la long
unsigned long long getLongX(tank* tank1);
unsigned long long getLongY(tank* tank1);

#endif
