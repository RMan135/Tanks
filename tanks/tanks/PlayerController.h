#pragma once
#include <SDL.h>
#include "tank.h"

struct PlayerController
{
	bool fwd, bkd, left, right, fire;
	SDL_Keycode btFwd, btBkd, btLeft, btRight, btFire;
	tank* ownedTank;

	void keyDown(SDL_Keycode key)
	{
		if (key == btFwd)
		{
			fwd = 1;
		}
		if (key == btBkd)
		{
			bkd = 1;
		}
		if (key == btLeft)
		{
			left = 1;
		}
		if (key == btRight)
		{
			right = 1;
		}
		if (key == btFire)
		{
			fire = 1;
		}
	}

	void keyUp(SDL_Keycode key)
	{
		if (key == btFwd)
		{
			fwd = 0;
		}
		if (key == btBkd)
		{
			bkd = 0;
		}
		if (key == btLeft)
		{
			left = 0;
		}
		if (key == btRight)
		{
			right = 0;
		}
		if (key == btFire)
		{
			fire = 0;
		}
	}

	void update()
	{
		if (fwd && !bkd)
			move(ownedTank, (fob)1);
		if (bkd && !fwd)
			move(ownedTank, (fob)-1);
		if (!left && right)
			turn(ownedTank, (lor)1);
		if (!right && left)
			turn(ownedTank, (lor)-1);
		if (fire)
			shoot(ownedTank);
	}

	void setPlayerOne()
	{
		btFwd = SDLK_w;
		btBkd = SDLK_s;
		btLeft = SDLK_a;
		btRight = SDLK_d;
		btFire = SDLK_SPACE;
	}

	void setPlayerTwo()
	{
		btFwd = SDLK_KP_8;
		btBkd = SDLK_KP_5;
		btLeft = SDLK_KP_4;
		btRight = SDLK_KP_6;
		btFire = SDLK_KP_0;
	}

	void reset()
	{
		fwd = bkd = left = right = fire = 0;
	}

	void addTank(tank *t)
	{
		ownedTank = t;
	}

	tank* getTank()
	{
		return ownedTank;
	}
};

