/*
	Stiti ce-i ala. Numa' ca un collisionBox poate sa fie si circle, nu numa' patrat. Aveti flagu' type care specifica care din tipuri e folosit.
*/

#ifndef COLLISIONBOX_HEADER
#define COLLISIONBOX_HEADER

#include "object.h"
#include "collision.h"

union collisionType = {square, circle};

struct collisionBox{
	collisionType type; 
	unsigned int x, y; // coltu' stanga sus
};

collisionBox* createCollisionBox();
void destroyCollisionBox();


// one day... I will learn templates... one day

bool checkCollision(object* object1, object* object2);
bool checkCollision(object* object1, tank* tank2);
bool checkCollision(tank* tank1, object* object2);
bool checkCollision(tank* tank1, tank* tank2);

#endif