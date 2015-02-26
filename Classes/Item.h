#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h";
#include "Entity.h"

class Item : public Entity
{
public:
	Item();
	~Item();

	void setPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	};
protected:
	float x, y;
	cocos2d::Sprite *sprite;
};

#endif