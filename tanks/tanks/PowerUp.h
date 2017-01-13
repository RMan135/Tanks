#pragma once
#include "coord.h"
#include "collision.h"
#include "Texture.h"

enum powerupCode { god, speed, damage, heal, oneshot };

class PowerUp
{
private:
	coords pos, dim;
	collisionBox *colBox;
	powerupCode type;
	unsigned long long duration;
	SDL_Renderer *renderTarget;
	Texture texture;

public:

	void setPowerUp(double x, double y, powerupCode t, SDL_Renderer *target, unsigned long long d = 5000);
	collisionBox* getColBox();
	unsigned long long getDuration();
	powerupCode getType();
	void show();
};

