#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "cocos2d.h"
class GameState;
class Player;

class Bullet : public Entity
{
public:
	Bullet(GameState *gs, Player *p, float dx, float dy);
	~Bullet();
	
	void update(float dt);
	void setVelocity(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	};
private:
	float dx, dy;
	cocos2d::Sprite *sprite;
};

#endif