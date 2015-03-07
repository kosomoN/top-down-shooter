#include "Wall.h"
#include "Entity.h"

Wall::Wall(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->entity_type = WALL;
}


Wall::~Wall()
{
}

void Wall::update(float dt)
{
	x_axis = true;
	y_axis = true;
}

void Wall::destroy() {}

void Wall::setPositionX(float x) {}
void Wall::setPositionY(float y) {}