/*
	tanki
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#define POWERUP_NUMBER 3 
#define MAX_TANK_NUMBER 4

#include "coord.h"

struct collisionBox;

enum powerupCode {ghost, speed, godmode}; // doar un sketch
enum lor {left = 1, right = -1}; // left or right
enum fob {forward = 1, backward = -1}; // forward or backward
enum projectileType {light, normal, heavy, explosive};

struct powerup{
	powerupCode power;
	unsigned long long expirationDate;
};

struct tank{
	collisionBox* colBox;
	unsigned int team;
	powerup* powerups;
	projectileType ammoType;
	unsigned int health, damageMod;
	double speed;
	position x, y;
	double incX100, multX;
	unsigned int rotation, turretRotation;
};

tank* tankVector[MAX_TANK_NUMBER];

tank* createTank(unsigned int team, unsigned int tileX, unsigned int tileY);
void destroyTank(tank* tank);

bool accelerate(tank* tank1, fob sense); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);
void aim(tank* tank1, unsigned int x, unsigned int y);
void act(tank* tank1); // AIu'; functia apelata in fiecare frame, pentru
					// fiecare tank

#endif
