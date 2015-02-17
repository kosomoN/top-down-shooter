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
	const static int STANDING = 0, WALKING = 1, ATTACKING = 2;
	int currentState;
	Node *baseNode;
	Animate *currentAnim;
	
	void update(float dt);
	void changeState(const int state);
	void setPositionX(float x);
	void setPositionY(float y);
private:
	Vector<Animation*> animations;
	GameState *gs;
	Sprite *sprite;
	float maxVelocity;
	const float DIAGONAL = sqrt(0.5f);

	void loadAnimations();
	void move();
	void updateInput();

	/* DEBUGGING TOOLS
	int getMilliCount();
	int getMilliSpan(int start);
	*/
};

#endif