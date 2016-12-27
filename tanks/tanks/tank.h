/*
	Self-explanatory.
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#include <vector>

union powerup = {speed, godmode}; // doar un sketch
union lor = {left, right}; // directie?

struct tank{
	collisionBox* colBox;
	unsigned int health;
	unsigned int speed;
	vector<powerup> powerUps;
};

tank* createTank();
void destroyTank();

bool move(tank* tank1); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);

#endif