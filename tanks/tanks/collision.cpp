#include "collision.h"
#include "tank.h"
#include "projectile.h"
#include "terrain.h"

collisionBox* createCollisionBox(tank* owner){
	collisionBox* box = new collisionBox;
	box->type = square;
	box->pos.x.doubleVal = owner->pos.x.doubleVal;
	box->pos.y.doubleVal = owner->pos.y.doubleVal;
	box->radius = TANK_SIZE;
	box->dim.x.doubleVal = owner->dim.x.doubleVal;
	box->dim.y.doubleVal = owner->dim.y.doubleVal;
	box->pos.type = coordType_double;
	box->rotation = owner->rotation;
	return box;
}

collisionBox* createCollisionBox(projectile* owner){
	collisionBox* box = new collisionBox;
	box->type = square;
	box->pos.x.doubleVal = owner->pos.x.doubleVal;
	box->pos.y.doubleVal = owner->pos.y.doubleVal;
	box->radius = TANK_SIZE;
	box->dim.x.doubleVal = owner->dim.x.doubleVal;
	box->dim.y.doubleVal = owner->dim.y.doubleVal;
	box->pos.type = coordType_double;
	box->rotation = owner->rotation;
	return box;
}

void destroyCollisionBox(collisionBox* box){
	delete box;
}

bool checkCollision(collisionBox* box1, collisionBox* box2){
	return 1;
}

bool checkEnvCollision(collisionBox* box1){ // coliziune cu imprejurarile (nu cu alt tanc)
	return 1;
}
