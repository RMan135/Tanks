/*
	Self-explanatory.
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#include <vector>
#include "collision.h"

union powerup = {speed, godmode}; // doar un sketch
union lor = {left, right}; // directie?

struct tank{
	collisionBox* colBox;
	unsigned int health;
	unsigned int speed, handling; // handlingu' e cat de usor se poate intoarce
	vector<powerup> powerUps;
	unsigned int rotation;
};

tank* createTank();
void destroyTank();

bool move(tank* tank1); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);
void act(tank* tank1); // AIu'; functia apelata in fiecare frame, pentru
		// fiecare tank

#endif