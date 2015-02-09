#include  "Player.h"

using namespace cocos2d;

Player::Player(Scene* scene, float x, float y)
{
	setPosition(x, y);

	sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(position);
	scene->addChild(sprite);
}

Sprite* Player::getSprite()
{
	return sprite;
}