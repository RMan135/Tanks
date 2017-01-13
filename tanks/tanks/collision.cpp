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
	box->radius = ((owner->dim.x.doubleVal / 2) + (owner->diagonal / 2)) / 2;
	box->dim = &owner->dim;
	box->rotation = &owner->rotation;
	return box;
}


void destroyCollisionBox(collisionBox* box){
	delete box;
}

template <class type1, class type2>
bool checkCollision(type1* obj1, type2* obj2){
	// celalalt phase
	double difX = abs(obj1->pos.x.doubleVal - obj2->pos.x.doubleVal);
	double difY = abs(obj1->pos.y.doubleVal - obj2->pos.y.doubleVal);
	if(difX < (obj1->dim.x.doubleVal + obj2->dim.x.doubleVal) / 2 && difY < (obj1->dim.x.doubleVal + obj2->dim.x.doubleVal) / 2)
		return 1;
	
	return 0;
}

template <class type>
bool checkEnvCollision(type* obj) {
	unsigned short iterPrec = 0;
	double vertexx;
	double vertexy;
	while (iterPrec < 8) {
		vertexx = obj->pos.x.doubleVal + cos(iterPrec * 45 * RADIAN) * obj->colBox->radius;
		vertexy = obj->pos.y.doubleVal + sin(iterPrec * 45 * RADIAN) * obj->colBox->radius;
		if (collisionMap.tiles[(long long)vertexx][(long long)vertexy])
			return 1;
		++iterPrec;
	}
	return 0;
}

template collisionBox* createCollisionBox<tank>(tank*);
template collisionBox* createCollisionBox<projectile>(projectile*);
template bool checkCollision<tank, tank>(tank*, tank*);
template bool checkCollision<tank, projectile>(tank*, projectile*);
template bool checkCollision<projectile, tank>(projectile*, tank*);
template bool checkEnvCollision<tank>(tank* obj);
template bool checkEnvCollision<projectile>(projectile* obj);