/*
	object:  zidurile sau proiectilele care le trage tancu'.
*/

#ifndef OBJECT_HEADER
#define OBJECT_HEADER

struct object{ // orice obiect nu e tank
	collisionBox* colBox;
	bool solid;
	unsigned int x, y; // coltu' stanga sus	
};

object* createObject();
void destroyObject();

#endif