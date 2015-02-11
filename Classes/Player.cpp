#include "Player.h"
#include "GameState.h"

using namespace cocos2d;

Player::Player(GameState *gs, Vec2 position)
{
	sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(position);
	gs->addChild(sprite);
	setPosition(position);
	this->gs = gs;
	this->maxVelocity = 16;
}

void Player::update(float dt)
{
	bool upKeyPressed = false, sideKeyPressed = false;
	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_W))
	{
		addVelocity(Vec2(0, 4));
		upKeyPressed = !upKeyPressed;
	}
	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_S))
	{
		addVelocity(Vec2(0, -4));
		upKeyPressed = !upKeyPressed;
	}

	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_A))
	{
		addVelocity(Vec2(-4, 0));
		sideKeyPressed = !sideKeyPressed;
	}
	if (gs->isKeyDown(EventKeyboard::KeyCode::KEY_D))
	{
		addVelocity(Vec2(4, 0));
		sideKeyPressed = !sideKeyPressed;
	}

	if (this->velocity.length() > maxVelocity)
	{
		setVelocity(velocity.getNormalized() * maxVelocity);
	}
	
	addVelocity(-getVelocity() * 0.4f);
	
	CCLOG("V: %f , %f", getVelocity().x, getVelocity().y);
	Player::addPosition(getVelocity());
}

void Player::setVelocity(Vec2 velocity)
{
	this->velocity = velocity;
}

void Player::addVelocity(Vec2 velocity)
{
	this->velocity.add(velocity);
}

void Player::setPosition(Vec2 pos)
{
	Entity::setPosition(pos);
	sprite->setPosition(pos);
}

void Player::addPosition(Vec2 pos)
{
	Entity::addPosition(pos);
	sprite->setPosition(getPosition());
}

Vec2 Player::getVelocity()
{
	return velocity;
}

Sprite* Player::getSprite()
{
	return sprite;
}