/*
	lista simplu inlantuita pentru proiectile

	o sa exista o instanta globala pentru proiectilele lansate
*/

#ifndef PROJECTILELIST_HEADER
#define PROJECTILELIST_HEADER

struct projectile;

struct projectileNode{
	projectile* payload;
	projectileNode* next;
};

struct projectileList{
	projectileNode* first;
};

void initProjectileList(projectileList& list);
void destroyList(projectileList& list);

void addProjNode(projectile* addedProjectile);
void delProjNode(projectile* addedProjectile);

#endif
