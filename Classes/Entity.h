#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

using namespace cocos2d;

class Entity
{
public:
	virtual void update(float dt) = 0;

	void setPosition(Vec2 position);
	void addPosition(Vec2 position);
	Vec2 getPosition();
protected:
	Vec2 position;
};
#endif