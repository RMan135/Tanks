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

template <class type1, class type2> bool checkCollision(type1* box1, type2* box2);
template <class type> bool checkEnvCollision(type* box1); // coliziune cu imprejurarile (nu cu alt tanc)
bool checkEnvCollisionAcF(collisionBox* box1);
bool checkEnvCollisionAcB(collisionBox* box1);
bool checkEnvCollisionTnL(collisionBox* box1);
bool checkEnvCollisionTnR(collisionBox* box1);

#endif
