#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
class GameState;

using namespace cocos2d;

class Player
{
public:
	Player(GameState *gs, float x, float y);
	~Player();

	float x, y;
	float dx = 0, dy = 0;
	float distX = 0, distY = 0;
	float movementMod = 1;
	const float WIDTH = 128, HEIGHT = 64;
	const float offset = (WIDTH + HEIGHT) * 0.22f; // Found through testing, 0.2f is safe 
	Node *baseNode;
	
	void update(float dt);
	void setPositionX(float x);
	void setPositionY(float y);
private:
	Vector<SpriteFrame*> animFrames;
	GameState *gs;
	Sprite *sprite;
	float maxVelocity;
	const float DIAGONAL = sqrt(0.5f);

	void move();
	void updateInput();
};

#endif