#include "tank.h"

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
	tank1->health = 100;
	tank1->damageMod = 1.0;
	tank1->speed = 0.1;
	tank1->rotation = 0;
	tank1->turretRotation = 0;
	tank1->stepX = speed;
	tank1->stepY = 0.0;
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
