#include "projectile.h"

void destroyProjectile(projectile* proj){
	//coliziunea nu e implementata inca
	//destroyCollisionBox(proj->colBox);
	delete proj;
}
