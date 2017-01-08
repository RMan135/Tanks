/*
	lista simplu inlantuita pentru proiectile

	o sa exista o instanta globala pentru proiectilele lansate
*/

#ifndef PROJECTILELIST_HEADER
#define PROJECTILELIST_HEADER

struct projectile;

struct projectileNode{
	projectile* payload;
	projectileNode *next, *prev;
};

struct projectileList{
	projectileNode* first;
};

extern projectileList projectilesShot;

void destroyProjNode(projectileNode* projNode);

void initProjectileList(projectileList& list);
void destroyList(projectileList& list);

void addProjNode(projectileNode*& lastNode, projectile* proj);
void addProjNode(projectileList& list, projectile* proj);
void delProjNode(projectileNode*& projNode);

#endif
