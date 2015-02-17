#include "Player.h"
#include "GameState.h"
#include <math.h>

// For debugging
//#include <sys/timeb.h>

using namespace cocos2d;

Player::Player(GameState *gs, float x, float y)
{
	baseNode = Node::create();
	sprite = Sprite::create();
	baseNode->addChild(sprite);

	loadAnimations();

	// Starting off, the player is standing
	changeState(STANDING);
	
	setPositionX(x);
	setPositionY(y);
	this->gs = gs;
	this->maxVelocity = 9;
}

Player::~Player()
{

}

void Player::loadAnimations()
{
	// Loading walk animation frames
	Vector<SpriteFrame *> animFrames;
	char str[100] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		sprintf(str, "walking_anim.png", i);
		auto frame = SpriteFrame::create(str, Rect((i % 4) * WIDTH, floor(i / 4) * HEIGHT, WIDTH, HEIGHT));
		animFrames.pushBack(frame);
	}

	// Creating walk animation from loaded frames
	auto *walkAnim = Animation::createWithSpriteFrames(animFrames, 0.08f);
	walkAnim->setLoops(-1);
	animations.pushBack(walkAnim);

	currentAnim = nullptr;
}

void Player::changeState(const int state)
{
	switch (state)
	{
	case STANDING:
		currentState = STANDING;
		if (currentAnim != nullptr)
			sprite->stopAction(currentAnim);
	
		sprite->setTexture("Player_standing.png");
		currentAnim = nullptr;
		break;
	case WALKING:
		currentState = WALKING;
		if (currentAnim != nullptr)
			sprite->stopAction(currentAnim);

		currentAnim = Animate::create(animations.at(0));
		sprite->runAction(currentAnim);
		break;
	case ATTACKING:
		currentState = ATTACKING;
		if (currentAnim != nullptr)
			sprite->stopAction(currentAnim);

		currentAnim = Animate::create(animations.at(1));
		sprite->runAction(currentAnim);
		break;
	default:
		CCLOG("Error: 'No such player state' (%i)", state);
		return;
	}

	CCLOG("Changing to state: %s", (state == STANDING ? "Standing" : state == WALKING ? "Walking" : state == ATTACKING ? "Attacking" : ""));
}

void Player::update(float dt)
{
	distX = gs->mouseX - (x + baseNode->getParent()->getPositionX());
	distY = -gs->mouseY + y + baseNode->getParent()->getPositionY(); // y is swapped
	float angle = CC_RADIANS_TO_DEGREES(atan2(distY, distX)) + 90;
	sprite->setRotation(angle);

	// Getting input
	updateInput();

	// Moving
	move();
}

void Player::move()
{
	float tempX = x + dx;
	float tempY = y + dy;
	bool x_axis = true, y_axis = true;

	// Checking rectangular hitboxes
	for (unsigned int i = 0; i < gs->mapHitboxes->getObjects().size(); i++)
	{
		ValueMap valMap = gs->mapHitboxes->getObjects().at(i).asValueMap();
		float valX = valMap["x"].asFloat();
		float valY = valMap["y"].asFloat();
		float valWidth = valMap["width"].asFloat();
		float valHeight = valMap["height"].asFloat();

		if (tempX - offset < valX + valWidth && tempX + offset > valX &&
			tempY - offset < valY + valHeight && tempY + offset > valY)
		{
			// 1. Was x-axis the frame before "intersecting"? if yes then disable y-axis else go to 2.
			// 2. Was y-axis the frame before "intersecting"? if yes then disable x-axis else do nothing

			if (x - offset < valX + valWidth && x + offset > valX)
				y_axis = false;
			else if (y - offset < valY + valHeight && y + offset > valY)
				x_axis = false;
		}
	}

	if (x_axis)
		setPositionX(tempX);
	if (y_axis)
		setPositionY(tempY);

	// Attacking is the most important and cannot be overridden
	if (abs(dx) > 0.1f || abs(dy) > 0.1f)
	{
		if (currentState != ATTACKING && currentState != WALKING)
			changeState(WALKING);
	}
	else
	{
		if (currentState != ATTACKING && currentState != STANDING)
			changeState(STANDING);
	}
}

void Player::updateInput()
{
	movementMod = 1;
	// Check if moving diagonally
	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_W) != gs->isKeyDown(EventKeyboard::KeyCode::KEY_S) &&
		gs->isKeyDown(EventKeyboard::KeyCode::KEY_A) != gs->isKeyDown(EventKeyboard::KeyCode::KEY_D))
	{
		movementMod = DIAGONAL;
	}

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_W))
		dy += 2 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_S))
		dy -= 2 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_A))
		dx -= 2 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_D))
		dx += 2 * movementMod;

	// Capping max velocity
	float length = sqrt(dx * dx + dy * dy);
	if (length > maxVelocity)
	{
		dx *= maxVelocity / length;
		dy *= maxVelocity / length;
	}

	// Applying friction
	dx *= 0.6f;
	dy *= 0.6f;
}

void Player::setPositionX(float x)
{
	this->x = x;
	baseNode->setPositionX(x);
}

void Player::setPositionY(float y)
{
	this->y = y;
	baseNode->setPositionY(y);
}

/* DEBUGGING TOOLS
int Player::getMilliCount(){
timeb tb;
ftime(&tb);
int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
return nCount;
}

int Player::getMilliSpan(int nTimeStart){
int nSpan = getMilliCount() - nTimeStart;
if (nSpan < 0)
nSpan += 0x100000 * 1000;
return nSpan;
}
*/