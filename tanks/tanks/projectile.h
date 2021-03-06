/*
	proiectilele cu care trage tancu'
*/

#ifndef PROJECTILE_HEADER 
#define PROJECTILE_HEADER

#include "coord.h"

#define PROJECTILE_SIZE 0.20833333

struct tank;
struct collisionBox;
struct projectileNode;

struct projectile{
	collisionBox *colBox;
	tank* owner;
	projectileNode* listPos;
	int damage;
	bool oneshot;
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
