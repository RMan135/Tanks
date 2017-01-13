/*
	Stiti ce-i ala. Numa' ca un collisionBox poate sa fie si circle, nu numa' patrat. Aveti flagu' type care specifica care din tipuri e folosit.
*/

#ifndef COLLISIONBOX_HEADER
#define COLLISIONBOX_HEADER

struct coords;
enum collisionType {square, circle};

struct collisionBox{
	collisionType type; 
	coords *pos, *dim;
	double radius;
	unsigned int *rotation;
};

template <class type> collisionBox* createCollisionBox(type* owner);
void destroyCollisionBox(collisionBox* box);

template <class type1, class type2> bool checkCollision(type1* obj1, type2* obj2);
template <class type> bool checkEnvCollision(type* obj);

#endif
