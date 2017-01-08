#include "collision.h"
#include "tank.h"
#include "projectile.h"
#include "terrain.h"
#include <cmath>
#define RADIAN 0.01745329251

template <class type>
collisionBox* createCollisionBox(type* owner){
	collisionBox* box = new collisionBox;
	box->type = square;
	box->pos = &owner->pos;
	box->radius = owner->dim.x.doubleVal;
	box->dim.x.doubleVal = owner->dim.x.doubleVal;
	box->dim.y.doubleVal = owner->dim.y.doubleVal;
	box->rotation = &owner->rotation;
	return box;
}


void destroyCollisionBox(collisionBox* box){
	delete box;
}

template <class type1, class type2>
bool checkCollision(type1* obj1, type2* obj2){
	// broad-phase
	double difX = obj1->pos.x.doubleVal - obj2->pos.x.doubleVal;
	double difY = obj1->pos.y.doubleVal - obj2->pos.y.doubleVal;
	if(difX > 3 && difY > 3)
		return 0;
	// celalalt phase
	return 1;
}

template <class type>
bool checkEnvCollision(type* obj){ // coliziune cu imprejurarile (nu cu alt tanc)
	double vertex1x = obj->pos.x.doubleVal + sin(((obj->rotation + 315) % 360) * RADIAN) * TANK_DIAGD2; 
	double vertex1y = obj->pos.y.doubleVal + cos(((obj->rotation + 315) % 360) * RADIAN) * TANK_DIAGD2;
	if(collisionMap.tiles[(long long)vertex1x][(long long)vertex1y])
		return 1;

	double vertex2x = obj->pos.x.doubleVal + sin(((obj->rotation + 45) % 360) * RADIAN) * TANK_DIAGD2; 
	double vertex2y = obj->pos.y.doubleVal + cos(((obj->rotation + 45) % 360) * RADIAN) * TANK_DIAGD2;
	if(collisionMap.tiles[(long long)vertex2x][(long long)vertex2y])
		return 1;
	
	unsigned int nextVexRot = obj->rotation + (90 - obj->rotation % 90);
	double nextVexx = (double)((long long)obj->pos.x.doubleVal) + 0.5;
	double nextVexy = (double)((long long)obj->pos.x.doubleVal) + 0.5;
	nextVexx += sin((nextVexRot % 360) * RADIAN) * TANK_DIAGD2;
	nextVexy += cos((nextVexRot % 360) * RADIAN) * TANK_DIAGD2;
	
	double m12 = (vertex2y - vertex1y) / (vertex2x - vertex1x), m1n = (nextVexx - vertex1x) / (nextVexy - vertex1y);
	if(m1n <= m12)
		return 1;
	return 0;
}

template collisionBox* createCollisionBox<tank>(tank*);
template collisionBox* createCollisionBox<projectile>(projectile*);
template bool checkCollision<tank, tank>(tank*, tank*);
template bool checkCollision<tank, projectile>(tank*, projectile*);
template bool checkCollision<projectile, tank>(projectile*, tank*);
template bool checkEnvCollision<tank>(tank*);
template bool checkEnvCollision<projectile>(projectile*);
