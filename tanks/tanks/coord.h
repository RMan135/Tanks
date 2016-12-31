/*
	pentru manage-uit coordonate
*/

#ifndef COORD_HEADER
#define COORD_HEADER

union coordinate {double doubleVal, long long longVal};
enum coordType {coordType_double, coordType_long};

struct position{
	coordinate x, y;
	coordType type;
};

void coordToDouble(position& pos); // converteste coordonatele la double
void coordToLong(position& pos); // converteste coordonatele la long

#endif
