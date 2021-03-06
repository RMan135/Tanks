#include "tank.h"
#include "collision.h"
#include "projectile.h"
#include "movement.h"
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
		//addPowerup(ret, powerupCode::god);
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
	tank1->maxHealth = 80 + type * 25;
	tank1->health = tank1->maxHealth;
	tank1->damageMod = 0.5 + type / 4;
	tank1->ammoType = projectileType::normal;
	tank1->nextShot = 0;
	tank1->cooldown = 350 * type;
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
}

void addDiff(tank* tank1, unsigned short howmuch) {
	tank1->maxHealth += 5 * howmuch;
	tank1->health = tank1->maxHealth;
	tank1->damageMod += 0.025 * howmuch;
	tank1->speed += 0.0025 * howmuch;
	tank1->rotationSpeed += (unsigned int)(0.3 * howmuch);
}

void subDiff(tank* tank1, unsigned short howmuch) {
	if (tank1->maxHealth - 5 * howmuch > 10) {
		tank1->maxHealth -= 5 * howmuch;
		tank1->health = tank1->maxHealth;
	}
	if(tank1->damageMod - 0.025 * howmuch > 0.1)
		tank1->damageMod -= 0.025 * howmuch;
	if(tank1->speed - 0.0025 * howmuch > 0.001)
		tank1->speed -= 0.0025 * howmuch;
	if(tank1->rotationSpeed - (unsigned int)(0.3 * howmuch) > 1)
		tank1->rotationSpeed -= (unsigned int)(0.3 * howmuch);
}

void destroyTank(tank* tank){
	{
		int i = 0;
		while(i < MAX_TANK_NUMBER){
			if(tankVector[i] == tank)
				break;
			i++;
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
	if(SDL_GetTicks() < tank1->nextShot)
		return;
	projectile* shot = createProjectile(tank1);
	unsigned int iterProjOS = 0;
	while (iterProjOS < MAX_PROJECTILES_ONSCREEN) {
		if (tank1->projOnScreen[iterProjOS] == nullptr)
			break;
		++iterProjOS;
	}
	tank1->projOnScreen[iterProjOS] = shot;
	tank1->nextShot = SDL_GetTicks() + tank1->cooldown;
}

void aim(tank* tank1, coords where){
	tank1->rotation = (360 + (unsigned int)(atan2(where.y.doubleVal - tank1->pos.y.doubleVal, where.x.doubleVal - tank1->pos.x.doubleVal) / RADIAN)) % 360;
	tank1->stepX = cos(tank1->rotation * RADIAN) * tank1->speed;
	tank1->stepY = sin(tank1->rotation * RADIAN) * tank1->speed;
}

void aim(tank* tank1, double wx, double wy) {
	tank1->rotation = (360 + (unsigned int)(atan2(wy - tank1->pos.y.doubleVal, wx - tank1->pos.x.doubleVal) / RADIAN)) % 360;
	tank1->stepX = cos(tank1->rotation * RADIAN) * tank1->speed;
	tank1->stepY = sin(tank1->rotation * RADIAN) * tank1->speed;
}

void addPowerup(tank* tank1, PowerUp* what){
	if(SDL_GetTicks() < what->nextAvail)
		return;
	switch(what->getType()){
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
	tank1->powerups[what->getType()] = SDL_GetTicks() + what->duration;
	what->nextAvail = SDL_GetTicks() + what->unavail;
}

void addPowerup(tank* tank1, powerupCode what) {
	switch (what) {
	case heal:
		if (tank1->health <= 0.5 * tank1->maxHealth)
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
	tank1->powerups[what] = SDL_GetTicks() + 500;
}


void updatePowerups(){
	unsigned long long curTicks = SDL_GetTicks();
	tank* curTank;
	int iterPower = 0;

	for(int iterTank = 0; iterTank < MAX_TANK_NUMBER; ++iterTank){
		curTank = tankVector[iterTank];

		if(curTank != NULL)
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

struct tankMovement
{
	bool isShooting = 0, gotOut = 0;
	double prevPosX = 0, prevPosY = 0;

	short nextPoint,
		endPoint,
		pointCoordsX[300],
		pointCoordsY[300],
		routeLength;
} t[4];

bool reachedNextPoint(double x1, double y1, short nr) {
	double x2 = (double)t[nr].pointCoordsX[t[nr].nextPoint];
	double y2 = (double)t[nr].pointCoordsY[t[nr].nextPoint];
	return ((abs(x1 - x2) < 0.2) && (abs(y1 - y2) < 0.2));
}


void act(tank* tank1, short nr) {
	if ((t[nr].nextPoint > t[nr].endPoint - 1) || (t[nr].gotOut == 1 && t[nr].isShooting == 0))
	{
		t[nr].nextPoint = 2;
		route(tank1->pos.x.doubleVal, tank1->pos.y.doubleVal, tankVector[0]->pos.x.doubleVal, tankVector[0]->pos.y.doubleVal,
			t[nr].pointCoordsX, t[nr].pointCoordsY, t[nr].routeLength);
		t[nr].endPoint = t[nr].routeLength;
		t[nr].gotOut = 0;
	}
	if(tankVector[0] != nullptr)
	if (canFire(tank1->pos.x.doubleVal, tank1->pos.y.doubleVal, tankVector[0]->pos.x.doubleVal, tankVector[0]->pos.y.doubleVal))
	{
		aim(tank1, tankVector[0]->pos.x.doubleVal, tankVector[0]->pos.y.doubleVal);
		shoot(tank1);
		t[nr].isShooting = 1;
		t[nr].gotOut = 1;
	}
	else
	{
		aim(tank1, t[nr].pointCoordsX[t[nr].nextPoint], t[nr].pointCoordsY[t[nr].nextPoint]);
		move(tank1, fob::forward);
		if (t[nr].prevPosX == tank1->pos.x.doubleVal && t[nr].prevPosY == tank1->pos.y.doubleVal)
			t[nr].nextPoint--;
		if (reachedNextPoint(tank1->pos.x.doubleVal, tank1->pos.y.doubleVal, nr))
			t[nr].nextPoint++;
		t[nr].isShooting = 0;
		t[nr].prevPosX = tank1->pos.x.doubleVal;
		t[nr].prevPosY = tank1->pos.y.doubleVal;
	}
}