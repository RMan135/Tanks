#include "PowerUp.h"


void PowerUp::setPowerUp(double x, double y, powerupCode t, SDL_Renderer *target, unsigned long long d)
{
	pos.x.doubleVal = x;
	pos.y.doubleVal = y;
	rotation = 0;
	type = t;
	duration = d;
	dim.x.doubleVal = 1.0;
	dim.y.doubleVal = 1.0;
	texture.setRenderTarget(target);
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

unsigned long long PowerUp::getDuration()
{
	return duration;
}

powerupCode PowerUp::getType()
{
	return type;
}

void PowerUp::show()
{
	texture.simpleRender(pos.x.longVal, pos.y.longVal);
}