/*
	Stiti ce-i ala. Numa' ca un collisionBox poate sa fie si circle, nu numa' patrat. Aveti flagu' type care specifica care din tipuri e folosit.
*/

#ifndef COLLISIONBOX_HEADER
#define COLLISIONBOX_HEADER

#include "coord.h"

struct tank;
enum collisionType {square, circle};

struct collisionBox{
	collisionType type; 
	position x, y;
	unsigned int radius; // ignorat daca type == square
};

collisionBox* createCollisionBox(collisionType initType, unsigned int initX, unsigned int initY, unsigned int initRadius);
void destroyCollisionBox(collisionBox* box);

bool checkCollision(collisionBox* box1, collisionBox* box2);
bool checkEnvCollision(collisionBox* box1); // coliziune cu imprejurarile (nu cu alt tanc)

#endif
