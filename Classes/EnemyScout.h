#ifndef ENEMY_SCOUT_H
#define ENEMY_SCOUT_H

#include "cocos2d.h"
#include "Entity.h"
#include "GameState.h"

using namespace cocos2d;

class EnemyScout : public Entity
{
public:
	EnemyScout(GameState *gs, float x, float y);
	~EnemyScout();
	
	GameState *gs;
	Sprite *sprite;
	float visibilityRange = 300;	
	
	unsigned int fireRate = 20; // ticks
	unsigned long lastShot = 0;
	
	
	virtual void update(float dt);
	virtual void destroy();
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	void shoot(float rotation);
private:
	float speed = 2.5f;
};

#endif
