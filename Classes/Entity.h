#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"
class GameState;

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void destroy() = 0;
	virtual void setPositionX(float x) = 0;
	virtual void setPositionY(float y) = 0;
	const static int PLAYER = 0, ENEMY = 1, BULLET = 2, WALL = 3;
	int entity_type;
	GameState *gs;
	float x = 0, y = 0;
	float dx = 0, dy = 0;
	float width, height;
	bool x_axis = false;
	bool y_axis = false;
};
#endif
