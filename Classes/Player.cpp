#include "Player.h"
#include "Bullet.h"
#include "Entity.h"
#include <math.h>

using namespace cocos2d;

Player::Player(GameState *gs, float x, float y)
{
	this->gs = gs;
	this->maxVelocity = 9;
	this->entity_type = PLAYER;
	this->width = WIDTH;
	this->height = WIDTH;
	this->x = x;
	this->y = y;

	baseNode = Node::create();
	sprite = Sprite::create();
	baseNode->addChild(sprite);
	loadAnimations();
	sprite->setAnchorPoint(Vec2(0.5f, 0.18f));
	baseNode->setPositionX(x);
	baseNode->setPositionY(y);

	// Starting off, the player is standing
	changeState(STANDING);

	gs->camera->addChild(baseNode);
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
	auto *walkAnim = Animation::createWithSpriteFrames(animFrames, 0.1f);
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

	// Update shooting
	lastShot++;

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

	x_axis = true;
	y_axis = true;
}

void Player::shoot(float rotation)
{
	if (lastShot >= fireRate)
	{
		gs->addEntity(new Bullet(gs, this, cosf(CC_DEGREES_TO_RADIANS(rotation)) * 24, -sinf(CC_DEGREES_TO_RADIANS(rotation)) * 24));
		lastShot = 0;
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
		dy += 3 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_S))
		dy -= 3 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_A))
		dx -= 3 * movementMod;

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_D))
		dx += 3 * movementMod;

	// Temporary to help development
	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_R))
		gs->reset();

	if (gs->mouseDown)
		shoot(sprite->getRotation() - 90);

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

void Player::destroy()
{
	gs->camera->removeChild(baseNode, true);
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