/*
	tanki
*/

#ifndef TANK_HEADER
#define TANK_HEADER

#define POWERUP_NUMBER 5
#define TIMED_POWERUPS 3
#define MAX_TANK_NUMBER 4
#define SCORE_UNIT 1000
#define MAX_PROJECTILES_ONSCREEN  5

#define TANK_SIZE 1.33333333

#include "coord.h"
#include "PowerUp.h"

struct collisionBox;
struct projectile;

enum lor {left = -1, right = 1}; // left or right (sens trigonometric sau invers, defapt...)
enum fob {forward = 1, backward = -1}; // forward or backward
enum projectileType {light, normal, heavy, explosive};
enum tankType {recon = 1, general = 2, frontline = 3};

struct tank{
	collisionBox* colBox;
	unsigned int team;
	unsigned long long powerups[POWERUP_NUMBER];
	projectileType ammoType;
	projectile* projOnScreen[MAX_PROJECTILES_ONSCREEN];
	short int health, maxHealth;
	double damageMod;
	double speed;
	coords pos, dim;
	double diagonal;
	double stepX, stepY;
	unsigned int rotation, rotationSpeed;
	bool alive;
	unsigned int score;
	unsigned long long nextShot, cooldown;
};

extern tank* tankVector[MAX_TANK_NUMBER];

void addPowerup(tank* tank1, PowerUp* what);
void addPowerup(tank* tank1, powerupCode what);
void updatePowerups();

tank* createTank(tankType type, unsigned int team, double initX, double initY);
void resetTank(tank* tank1, tankType type, unsigned int team, double initX, double initY);
void destroyTank(tank* tank);

void changeAmmo(tank* tank1, projectileType ammo);
bool move(tank* tank1, fob sense); // returneaza 0 daca nu poate
bool turn(tank* tank1, lor direction);
void shoot(tank* tank1);
void aim(tank* tank1, coords where);
void aim(tank* tank1, double wx, double wy);
void act(tank* tank1); // AIu'; functia apelata in fiecare frame, pentru
					// fiecare tank

#endif
