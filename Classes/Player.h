#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
class GameState;
#include "Entity.h"

class Player : public virtual Entity
{
public:
	Player(GameState *s, Vec2 position);

	void update(float dt);
	void setVelocity(Vec2 velocity);
	void addVelocity(Vec2 velocity);
	void setPosition(Vec2 pos);
	void addPosition(Vec2 pos);
	Vec2 getVelocity();
	Sprite* getSprite();
private:
	Sprite *sprite;
	GameState *gs;
	Vec2 velocity;
	float maxVelocity;
};

#endif