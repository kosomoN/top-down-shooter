#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(float x, float y, float width, float height);
	~Wall();
	
	virtual void update(float dt);
	virtual void destroy();
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
};

#endif