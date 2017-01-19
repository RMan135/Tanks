#include "PowerUp.h"

//PowerUp* powerUpVector[MAX_POWERUP_NUMBER];

void PowerUp::setPowerUp(double x, double y, powerupCode t, unsigned long long d)
{
	pos.x.doubleVal = x;
	pos.y.doubleVal = y;
	nextAvail = 0;
	unavail = 10000;
	rotation = 0;
	type = t;
	duration = d;
	dim.x.doubleVal = 1.0;
	dim.y.doubleVal = 1.0;
	switch (type)
	{
	case god:
		texture.loadTexture("media/invulnerable.png");
		break;
	case speed:
		texture.loadTexture("media/speedup.png");
		break;
	case damage:
		texture.loadTexture("media/doubledamage.png");
		break;
	case heal:
		texture.loadTexture("media/healthpack.png");
		break;
	case oneshot:
		texture.loadTexture("media/oneshotkill.png");
		break;
	}
	createCollisionBox(this);
}

collisionBox* PowerUp::getColBox()
{
	return colBox;
}

powerupCode PowerUp::getType()
{
	return type;
}

void PowerUp::show()
{
	if(SDL_GetTicks() > nextAvail)
		texture.simpleRender(pos.x.longVal, pos.y.longVal);
}