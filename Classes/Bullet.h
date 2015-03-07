#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#include "Entity.h"
class GameState;
class Player;

class Bullet : public Entity
{
public:
	Bullet(GameState *gs, Entity *e, float dx, float dy);
	~Bullet();

	virtual void update(float dt);
	virtual void destroy();
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	void setVelocity(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	};
private:
	cocos2d::Sprite *sprite;
};

#endif
