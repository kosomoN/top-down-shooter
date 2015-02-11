#include "Entity.h"

void Entity::setPosition(Vec2 position)
{
	this->position = position;
}

void Entity::addPosition(Vec2 position)
{
	this->position.x += position.x;
	this->position.y += position.y;
}

Vec2 Entity::getPosition()
{
	return position;
}
