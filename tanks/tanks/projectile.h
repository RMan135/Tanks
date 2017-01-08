/*
	proiectilele cu care trage tancu'
*/

#ifndef PROJECTILE_HEADER 
#define PROJECTILE_HEADER

#include "coord.h"
#include "collision.h"

struct tank;

struct projectile{
	collisionBox *colBox;
	tank* owner;
	int damage;
	coords pos, dim;
	double diagonal;
	double stepX, stepY; // determina miscarea proiectilului
	double speed; // folosita la calcularea miscarii
	unsigned int rotation;
};

projectile* createProjectile(tank* shooter);
void destroyProjectile(projectile* proj);

bool exist(projectile* proj); // proiectilu' face ce stie mai bine

#endif
