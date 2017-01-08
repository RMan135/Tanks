#include "projectilelist.h"
#include "projectile.h"

projectileList projectilesShot;

void initProjList(projectileList& list){
	list.first = nullptr;
}

void destroyProjNode(projectileNode* projNode){
	destroyProjectile(projNode->payload);
	delete projNode;
}

void destroyList(projectileList& list){
	if(list.first != nullptr){
		projectileNode *iterProjNode = list.first, *iterHook;
		while(iterProjNode->next != nullptr){
			iterHook = iterProjNode->next;
			destroyProjNode(iterProjNode);
			iterProjNode = iterHook;
		}
		destroyProjNode(iterProjNode);
		list.first = nullptr;
	}
}

void addProjNode(projectileNode*& lastNode, projectile* proj){
	lastNode->next = new projectileNode;
	lastNode->next->next = nullptr;
	lastNode->next->prev = lastNode;
	lastNode->next->payload = proj;
	lastNode->next->payload->listPos = lastNode->next;
}

void addProjNode(projectileList& list, projectile* proj){
	if(list.first != nullptr){
		projectileNode *iterProj = list.first;
		while(iterProj->next != nullptr)
			iterProj = iterProj->next;
		addProjNode(iterProj, proj);
	}else{
		list.first = new projectileNode;
		list.first->payload = proj;
		list.first->next = nullptr;
		list.first->prev = nullptr;
		list.first->payload->listPos = list.first;
	}
}

void delProjNode(projectileNode*& projNode){ // sa presunem ca nu trimitem si nullptr ca parametru
	bool prevNull = projNode->prev == nullptr, nextNull = projNode->next == nullptr;
	if(!prevNull && !nextNull){
		projNode->next->prev = projNode->prev;
		projNode->prev->next = projNode->next;
		destroyProjNode(projNode);
	}else if(!prevNull && nextNull){
		projNode->prev->next = nullptr;
		destroyProjNode(projNode);
	}else if(prevNull && !nextNull){
		projectileNode* nextToDelNode = projNode->next;
		destroyProjNode(projNode);
		projNode = nextToDelNode;
	}else if(prevNull && nextNull){
		destroyProjNode(projNode);
		projNode = nullptr;
	}
}
