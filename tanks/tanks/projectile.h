/*
	proiectilele cu care trage tancu'
*/

#ifndef PROJECTILE_HEADER 
#define PROJECTILE_HEADER

#include "projectilelist.h"
#include "coord.h"

struct tank;
struct collisionBox;

struct projectile{
	collisionBox *colBox;
	tank* owner;
	int damage;
	position x, y; // centrul, in pixeli
	double incX100, multX; // determina miscarea proiectilului
	double speed; // folosita la calcularea miscarii
	int rotation;
};

extern projectileList projectilesShot;

projectile* createProjectile(tank* shooter);
void destroyProjectile(projectile* proj);

void exist(projectile* proj); // proiectilu' face ce stie mai bine

#endif
