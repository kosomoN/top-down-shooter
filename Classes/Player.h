#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player(cocos2d::Scene* scene, float x, float y);
	cocos2d::Sprite* getSprite();

private:
	cocos2d::Sprite *sprite;
};

#endif