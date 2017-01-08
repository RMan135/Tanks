#include "projectile.h"
#include "tank.h"
#include "projectilelist.h"
#include <cmath>
#define RADIAN 0.01745329
#define SQRT2 1.41421356

/*
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
*/

projectile* createProjectile(tank* shooter){
	projectile* shotProj = new projectile;
	shotProj->owner = shooter;
	shotProj->damage = 25 + (shooter->ammoType * 20);
	shotProj->speed = 0.5 - (shooter->ammoType * 0.075);
	shotProj->oneshot = shooter->powerups[oneshot];
	shotProj->pos.x.doubleVal = shooter->pos.x.doubleVal;
	shotProj->pos.y.doubleVal = shooter->pos.y.doubleVal;
	shotProj->dim.x.doubleVal = PROJECTILE_SIZE;
	shotProj->dim.y.doubleVal = PROJECTILE_SIZE;
	shotProj->diagonal = shotProj->dim.x.doubleVal * SQRT2;
	shotProj->rotation = shooter->rotation;
	shotProj->stepX = sin((shotProj->rotation % 360) * RADIAN) * speed;
	shotProj->stepY = cos((shotProj->rotation % 360) * RADIAN) * speed;
	return shotProj;
}

void destroyProjectile(projectile* proj){
	destroyCollisionBox(proj->colBox);
	delete proj;
}

bool exist(projectile* proj){ // proiectilu' face ce stie mai bine
	proj->pos.x.doubleVal += proj->stepX;
	proj->pos.y.doubleVal += proj->stepY;
	if(!checkEnvCollision(proj)){
		int i = 0;
		while(i < MAX_TANK_NUMBER){
			if(tankVector[i] != proj->owner && tankVector[i] != nullptr)
				if(checkCollision(proj, tankVector[i]))
					break;
			++i;
		}
		if(i == MAX_TANK_NUMBER)
			return 1;
		tankVector[i]->health -= proj->damage;
		if(tankVector[i]->health <= 0 || proj->oneshot)
			tankVector[i]->alive = 0;
	}
	delProjNode(proj->listPos);
	destroyProjectile(proj);
	return 0;
}

