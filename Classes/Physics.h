#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameState.h"
#include "Entity.h"

class Physics
{
public:
	Physics(GameState *gs);
	~Physics();

	void resolveCollision(Entity *a, Entity *b);
	void collideWithWall(Entity *ent, Entity *wall);
	void update();
private:
	GameState *gs;
};
#endif
