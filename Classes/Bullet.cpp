#include "Bullet.h"
#include "GameState.h"
#include "Player.h"

Bullet::Bullet(GameState *gs, Player *p, float dx, float dy) :dx(dx), dy(dy)
{
	x = p->x;
	y = p->y;
	sprite = cocos2d::Sprite::create("Bullet.png");
	sprite->setPosition(Vec2(x, y));
	gs->camera->addChild(sprite);
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	x += dx;
	y += dy;
	sprite->setPositionX(x);
	sprite->setPositionY(y);
}
