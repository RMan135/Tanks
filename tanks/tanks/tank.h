/*
	tanki
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#define POWERUP_NUMBER 5
#define TIMED_POWERUPS 3
#define MAX_TANK_NUMBER 4

#define TANK_SIZE 32

#include "coord.h"
#include "collision.h"

struct collisionBox;

enum powerupCode {god, speed, damage, heal, oneshot};
enum lor {left = 1, right = -1}; // left or right
enum fob {forward = 1, backward = -1}; // forward or backward
enum projectileType {light, normal, heavy, explosive};

struct tank{
	collisionBox* colBox;
	unsigned int team;
	unsigned long long powerups[POWERUP_NUMBER];
	projectileType ammoType;
	short int health, maxHealth;
	double damageMod;
	double speed;
	coords pos, dim;
	double diagonal;
	double stepX, stepY;
	unsigned int rotation, turretRotation;
	bool alive;
};

extern tank* tankVector[MAX_TANK_NUMBER];

void addPowerup(tank* tank1, powerupCode what);
void updatePowerups();

tank* createTank(unsigned int team, double initX, double initY);
void resetTank(tank* tank1, unsigned int team, double initX, double initY);
void destroyTank(tank* tank);

bool move(tank* tank1, fob sense); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);
void aim(tank* tank1, coords where);
void act(tank* tank1); // AIu'; functia apelata in fiecare frame, pentru
					// fiecare tank

#endif
