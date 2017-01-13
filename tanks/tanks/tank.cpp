#include "tank.h"
#include "collision.h"
#include "projectile.h"
#include "SDL.h"
#include <cmath>
#define RADIAN 0.01745329
#define SQRT2 1.41421356

tank* tankVector[MAX_TANK_NUMBER];

tank* createTank(tankType type, unsigned int team, double initX, double initY){
	tank* ret = nullptr;
	int i = 0;
	while(i < MAX_TANK_NUMBER){
		if(tankVector[i] == nullptr)
			break;
		++i;
	}
	if(i != MAX_TANK_NUMBER){
		ret = new tank;
		tankVector[i] = ret;
		ret->score = 0;
		resetTank(ret, type, team, initX, initY);
		int iterProjOS = 0;
		while (iterProjOS < MAX_PROJECTILES_ONSCREEN) {
			ret->projOnScreen[iterProjOS] = nullptr;
			++iterProjOS;
		}
		ret->colBox = createCollisionBox(ret);
	}
	return ret;
}

void resetTank(tank* tank1, tankType type, unsigned int team, double initX, double initY){
	tank1->team = team;
	tank1->dim.x.doubleVal = TANK_SIZE;
	tank1->dim.y.doubleVal = TANK_SIZE;
	tank1->dim.type = coordType_double;
	tank1->pos.x.doubleVal = initX + tank1->dim.x.doubleVal / 2;
	tank1->pos.y.doubleVal = initY + tank1->dim.y.doubleVal / 2;
	tank1->pos.type = coordType_double;
	tank1->diagonal = SQRT2 * tank1->dim.x.doubleVal;
	tank1->maxHealth = 80 + type * 20;
	tank1->health = tank1->maxHealth;
	tank1->damageMod = 0.8 + type / 10;
	tank1->speed = 0.075 + 1 / (type * 20) ;
	tank1->rotation = 0;
	tank1->rotationSpeed = 4 - type;
	tank1->stepX = tank1->speed;
	tank1->stepY = 0.0;
	tank1->alive = 1;

	int i = 0;
	while(i < POWERUP_NUMBER){
		tank1->powerups[i] = 0;
		++i;
	}
	addPowerup(tank1, god);
}

void destroyTank(tank* tank){
	{
		int i = 0;
		while(i < MAX_TANK_NUMBER){
			if(tankVector[i] == tank)
				break;
		}
		if(i < MAX_TANK_NUMBER){
			tankVector[i] = nullptr;
			destroyCollisionBox(tank->colBox);
			delete tank;
		}
	}
}

bool move(tank* tank1, fob sense){ // returneaza 0 daca nu poate
	tank1->pos.x.doubleVal += tank1->stepX * sense;
	tank1->pos.y.doubleVal += tank1->stepY * sense;
	if(!checkEnvCollision(tank1)){ //!checkEnvCollision1Side(tank1)
		int i = 0;
		while(i < MAX_TANK_NUMBER){
			if(tankVector[i] != tank1 && tankVector[i] != nullptr)
				if(checkCollision(tank1, tankVector[i]))
					break;
			++i;
		}
		if(i == MAX_TANK_NUMBER)
			return 1;        
	}
	tank1->pos.x.doubleVal -= tank1->stepX * sense;
	tank1->pos.y.doubleVal -= tank1->stepY * sense;
	return 0;
}

bool turn(tank* tank1, lor direction){
	tank1->rotation = (360 + tank1->rotation + tank1->rotationSpeed * direction) % 360;
	if(checkEnvCollision(tank1)){
		tank1->rotation = (360 + tank1->rotation - tank1->rotationSpeed * direction) % 360;
		return 0;
	}
	tank1->stepX = (double)(cos(tank1->rotation * RADIAN) * tank1->speed);
	tank1->stepY = (double)(sin(tank1->rotation * RADIAN) * tank1->speed);
	return 1;
}

void changeAmmo(tank* tank1, projectileType ammo) {
	tank1->ammoType = ammo;
}

void shoot(tank* tank1) {
	projectile* shot = createProjectile(tank1);
	unsigned int iterProjOS = 0;
	while (iterProjOS < MAX_PROJECTILES_ONSCREEN) {
		if (tank1->projOnScreen[iterProjOS] == nullptr)
			break;
		++iterProjOS;
	}
	tank1->projOnScreen[iterProjOS] = shot;
}

void aim(tank* tank1, coords where){
	tank1->rotation = (long long)(atan2(where.y.doubleVal - tank1->pos.y.doubleVal, where.x.doubleVal - tank1->pos.x.doubleVal) / RADIAN) % 360;
	tank1->stepX = (double)(cos(tank1->rotation * RADIAN) * tank1->speed);
	tank1->stepY = (double)(sin(tank1->rotation * RADIAN) * tank1->speed);
}

void addPowerup(tank* tank1, powerupCode what){
	switch(what){
		case heal:
		if(tank1->health == 0.5 * tank1->maxHealth)
			tank1->health = tank1->maxHealth;
		else tank1->health += 0.5 * tank1->maxHealth;
		break;

		case damage:
		tank1->damageMod = 2 * tank1->damageMod;
		break;

		case oneshot:
		tank1->powerups[oneshot] += 3;
		break;
	}
	tank1->powerups[what] = SDL_GetTicks() + 2500 * what;
}

void updatePowerups(){
	unsigned long long curTicks = SDL_GetTicks();
	tank* curTank;
	int iterPower = 0;

	for(int iterTank = 0; iterTank < MAX_TANK_NUMBER; ++iterTank){
		curTank = tankVector[iterTank];

		while(iterPower < TIMED_POWERUPS){
			switch(curTank->powerups[iterPower]){
				case speed:
				if(curTicks > curTank->powerups[iterPower]){
					curTank->speed = 0.5 * curTank->speed;
					curTank->powerups[iterPower] = 0;
				}
				break;
				
				case damage:
				if(curTicks > curTank->powerups[iterPower]){
					curTank->damageMod = 0.5 * curTank->damageMod;
					curTank->powerups[iterPower] = 0;
				}
				break;

				case god:
				if(curTicks > curTank->powerups[iterPower]){
					curTank->powerups[iterPower] = 0;
				}
				break;

				default:
				break;
			}
			++iterPower;
		}
	}
}
