#include "Bullet.h"
#include "Entity.h"
#include "GameState.h"
#include "Player.h"

Bullet::Bullet(GameState *gs, Entity *e, float dx, float dy)
{
	this->entity_type = BULLET;
	this->gs = gs;
	this->dx = dx;
	this->dy = dy;
	x = e->x + dx * 2;
	y = e->y + dy * 2;
	sprite = cocos2d::Sprite::create("Bullet.png");
	sprite->setPosition(Vec2(x, y));
	this->width = sprite->getTexture()->getPixelsWide();
	this->height = sprite->getTexture()->getPixelsHigh();
	gs->camera->addChild(sprite);
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	x_axis = true;
	y_axis = true;
}

void Bullet::destroy()
{
	gs->camera->removeChild(sprite, true);
}

void Bullet::setPositionX(float x)
{
	this->x = x;
	sprite->setPositionX(x);
}

void Bullet::setPositionY(float y)
{
	this->y = y;
	sprite->setPositionY(y);
}
