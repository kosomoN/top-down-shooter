#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

class Entity
{
public:
	Entity();
	~Entity();
	void setPosition(float x, float y);
protected:
	cocos2d::Vec2 position;
};
#endif