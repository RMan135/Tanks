/*
	Stiti ce-i ala. Numa' ca un collisionBox poate sa fie si circle, nu numa' patrat. Aveti flagu' type care specifica care din tipuri e folosit.
*/

#ifndef COLLISIONBOX_HEADER
#define COLLISIONBOX_HEADER

#include "coord.h"

struct tank;
struct projectile;
enum collisionType {square, circle};

struct collisionBox{
	collisionType type; 
	coords pos, dim;
	double radius; // ignorat daca type == square
	double rotation;
};

collisionBox* createCollisionBox(tank* owner);
collisionBox* createCollisionBox(projectile* owner);
collisionBox* createCollisionBox(double initX, double initY, double initRotation);
collisionBox* createCollisionBox(double initRadius, double initRotation);
void destroyCollisionBox(collisionBox* box);

bool checkCollision(collisionBox* box1, collisionBox* box2);
bool checkEnvCollision(collisionBox* box1); // coliziune cu imprejurarile (nu cu alt tanc)
bool checkEnvCollisionAcF(collisionBox* box1);
bool checkEnvCollisionAcB(collisionBox* box1);
bool checkEnvCollisionTnL(collisionBox* box1);
bool checkEnvCollisionTnR(collisionBox* box1);

#endif
