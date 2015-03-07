#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Entity.h"
#include "GameState.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	Player(GameState *gs, float x, float y);
	~Player();

	float distX = 0, distY = 0;
	float movementMod = 1;
	const float WIDTH = 128, HEIGHT = 64;
	const static int STANDING = 0, WALKING = 1, ATTACKING = 2;
	unsigned int fireRate = 20; // ticks
	unsigned long lastShot = 0;
	int currentState;
	Node *baseNode;
	Animate *currentAnim;
	
	virtual void update(float dt);
	virtual void destroy();
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	void shoot(float rotation);
	void changeState(const int state);
private:
	Vector<Animation*> animations;
	Sprite *sprite;
	float maxVelocity;
	const float DIAGONAL = sqrt(0.5f);

	void loadAnimations();
	void updateInput();
};

#endif
