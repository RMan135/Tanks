#include "tank.h"
#include "SDL.h"
#include <cmath>
#define RADIAN 0.01745329
#define SQRT2 1.41421356

tank* tankVector[MAX_TANK_NUMBER];

tank* createTank(unsigned int team, double initX, double initY){
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
		resetTank(ret, team, initX, initY);
		ret->colBox = createCollisionBox(ret);
	}
	return ret;
}

void resetTank(tank* tank1, unsigned int team, double initX, double initY){
	tank1->team = team;
	tank1->pos.x.doubleVal = initX;
	tank1->pos.y.doubleVal = initY;
	tank1->dim.x.doubleVal = TANK_SIZE;
	tank1->dim.y.doubleVal = TANK_SIZE;
	tank1->diagonal = SQRT2 * tank1->dim.x.doubleVal;
	tank1->maxHealth = 100;
	tank1->health = 100;
	tank1->damageMod = 1.0;
	tank1->speed = 0.1;
	tank1->rotation = 0;
	tank1->turretRotation = 0;
	tank1->stepX = speed;
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
	tank1->pos.x.doubleVal += tank1->stepX;
	tank1->pos.y.doubleVal += tank1->stepY;
	if(!checkEnvCollision(tank1)){
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
	tank1->pos.x.doubleVal -= tank1->stepX;
	tank1->pos.y.doubleVal += tank1->stepY;
	return 0;
}

bool turn(tank* tank1, lor direction){
	if(!checkEnvCollision(tank1)){
		return 0;
	}
}

void shoot(tank* tank1){

}

void aim(tank* tank1, coords where){

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
