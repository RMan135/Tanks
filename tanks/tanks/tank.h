/*
	tanki
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#define POWERUP_NUMBER 3 
#define MAX_TANK_NUMBER 4

#define TANK_SIZE 32
#define TANK_DIAG 45.2548339958
#define TANK_DIAGD2 22.6274169979

#include "coord.h"
#include "collision.h"

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
	coords pos, dim;
	double incX100, multX;
	unsigned int rotation, turretRotation;
};

extern tank* tankVector[MAX_TANK_NUMBER];

tank* createTank(unsigned int team, double initX, double initY);
void destroyTank(tank* tank);

bool accelerate(tank* tank1, fob sense); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);
void aim(tank* tank1, double x, double y);
void act(tank* tank1); // AIu'; functia apelata in fiecare frame, pentru
					// fiecare tank

#endif
