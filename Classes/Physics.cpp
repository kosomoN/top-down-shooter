#include "Physics.h"

Physics::Physics(GameState *gs)
{
	this->gs = gs;
}

Physics::~Physics()
{

}

void Physics::resolveCollision(Entity *a, Entity *b)
{
	/*
	Checks every collision per entitytype and handles them accordingly
	*/

	if((a->entity_type == Entity::BULLET && b->entity_type == Entity::ENEMY) ||
		b->entity_type == Entity::BULLET && a->entity_type == Entity::ENEMY)
	{
		// Both the bullet and the enemy will be destroyed
		gs->removeEntity(a);
		gs->removeEntity(b);
	}
	else if ((a->entity_type == Entity::PLAYER && b->entity_type == Entity::ENEMY) ||
			(b->entity_type == Entity::PLAYER && a->entity_type == Entity::ENEMY))
	{
		//Game Over - resets game
		gs->reset();
	}
	else if ((a->entity_type == Entity::PLAYER || a->entity_type == Entity::ENEMY) && b->entity_type == Entity::WALL)
	{
		collideWithWall(a, b);
	}
	else if (a->entity_type == Entity::WALL && (b->entity_type == Entity::PLAYER || b->entity_type == Entity::ENEMY))
	{
		collideWithWall(b, a);
	}
	else if (a->entity_type == Entity::BULLET && b->entity_type == Entity::WALL)
	{
		// Only the bullet will be destroyed
		gs->removeEntity(a);
	}
	else if (b->entity_type == Entity::BULLET && a->entity_type == Entity::WALL)
	{
		// Only the bullet will be destroyed
		gs->removeEntity(b);
	}
}

void Physics::collideWithWall(Entity *ent, Entity *wall)
{
	// Restricting access to axis if colliding with wall
	if ((wall->width + ent->width) / 2 - abs(wall->x - ent->x) < (wall->height + ent->height) / 2 - abs(wall->y - ent->y))
		ent->x_axis = false;
	else
		ent->y_axis = false;
}

void Physics::update()
{
	for(unsigned int i = 0; i < gs->entities.size(); i++)
	{
		for (unsigned int j = i + 1; j < gs->entities.size(); j++)
		{
			Entity *a = gs->entities.at(i);
			Entity *b = gs->entities.at(j);

			// Checking middle points of rectangles against widths and heights
			if (abs((a->x + a->dx) - (b->x + b->dx)) < (b->width + a->width) / 2)
				if (abs((a->y + a->dy) - (b->y + b->dy)) < (b->height + a->height) / 2)
					resolveCollision(a, b);
		}
	}

	// Moving entities if they are allowed by axis
	for (unsigned int k = 0; k < gs->entities.size(); k++)
	{
		Entity *a = gs->entities.at(k);
		if (a->entity_type != Entity::WALL)
		{
			if (a->x_axis)
				a->setPositionX(a->x + a->dx);

			if (a->y_axis)
				a->setPositionY(a->y + a->dy);
		}
	}
}
