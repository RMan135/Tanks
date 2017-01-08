#include "projectile.h"

void destroyProjectile(projectile* proj){
	destroyCollisionBox(proj->colBox);
	delete proj;
}
