#include "projectile.h"
#include "tank.h"
#include "collision.h"
#include <cmath>
#define RADIAN 0.01745329
#define SQRT2 1.41421356

projectile* createProjectile(tank* shooter){
	projectile* shotProj = new projectile;
	shotProj->owner = shooter;
	shotProj->damage = (int)(25 + (shooter->ammoType * 15) * shooter->damageMod);
	shotProj->speed = 0.1 - (double)(shooter->ammoType * 0.02);
	shotProj->oneshot = shooter->powerups[oneshot];
	if(shooter->powerups[oneshot])
		--shooter->powerups[oneshot];
	shotProj->pos.x.doubleVal = shooter->pos.x.doubleVal;
	shotProj->pos.y.doubleVal = shooter->pos.y.doubleVal;
	shotProj->pos.type = shooter->pos.type;
	shotProj->dim.x.doubleVal = PROJECTILE_SIZE;
	shotProj->dim.y.doubleVal = PROJECTILE_SIZE;
	shotProj->dim.type = shooter->pos.type;
	shotProj->diagonal = shotProj->dim.x.doubleVal * SQRT2;
	shotProj->rotation = shooter->rotation;
	shotProj->stepX = (double)(cos((shotProj->rotation % 360) * RADIAN) * 0.3);
	shotProj->stepY = (double)(sin((shotProj->rotation % 360) * RADIAN) * 0.3);
	shotProj->colBox = createCollisionBox(shotProj);
	return shotProj;
}

void destroyProjectile(projectile* proj){
	unsigned int iterNode = 0;
	while (iterNode < MAX_PROJECTILES_ONSCREEN) {
		if (proj->owner->projOnScreen[iterNode] == proj) {
			proj->owner->projOnScreen[iterNode] = nullptr;
			break;
		}
		++iterNode;
	}
	destroyCollisionBox(proj->colBox);
	delete proj;
	proj = nullptr;
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
		if(tankVector[i]->powerups[god] == 0)
			tankVector[i]->health -= proj->damage;
		if(tankVector[i]->health <= 0 || proj->oneshot) {
			tankVector[i]->alive = 0;
			proj->owner->score += 1 * SCORE_UNIT;
		}
	}
	destroyProjectile(proj);
	return 0;
}

