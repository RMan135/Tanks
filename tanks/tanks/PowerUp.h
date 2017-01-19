#pragma once
#include "coord.h"
#include "collision.h"
#include "Texture.h"

#define MAX_POWERUP_NUMBER 4

enum powerupCode { god, speed, damage, heal, oneshot };

class PowerUp
{
private:
	
	powerupCode type;
	SDL_Renderer *renderTarget;
	Texture texture;

public:

	coords pos, dim;
	collisionBox *colBox;
	unsigned int rotation;
	unsigned long long duration, nextAvail, unavail;

	void setPowerUp(double x, double y, powerupCode t, unsigned long long d = 5000);
	collisionBox* getColBox();
	powerupCode getType();
	void show();
};

//PowerUp* powerUpVector[MAX_POWERUP_NUMBER];