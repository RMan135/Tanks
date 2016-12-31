/*
	proiectilele cu care trage tancu'
*/

#ifndef PROJECTILE_HEADER 
#define PROJECTILE_HEADER

#include "projectilelist.h"

struct tank;
struct collisionBox;

struct projectile{
	collisionBox *colBox;
	tank* owner;
	int damage;
	unsigned int x, y; // centrul, in pixeli
	unsigned int incX100, multX, bufferX; // determina miscarea proiectilului
	int speed; // folosita la calcularea miscarii
	unsigned int rotation;
};

projectileList projectilesShot;

projectile* createProjectile(tank* shooter);
void destroyProjectile(projectile* proj);

void exist(projectile* proj); // proiectilu' face ce stie mai bine

#endif
