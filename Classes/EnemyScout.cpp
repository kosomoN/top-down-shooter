#include "EnemyScout.h"
#include "Bullet.h"
#include "Player.h"
#include "Entity.h"
#include <math.h>

EnemyScout::EnemyScout(GameState *gs, float x, float y)
{
	sprite = Sprite::create("EnemyScout.png");
	this->entity_type = ENEMY;
	this->gs = gs;
	this->x = x;
	this->y = y;
	sprite->setPositionX(x);
	sprite->setPositionY(y);
	this->width = sprite->getTexture()->getPixelsWide();
	this->height = sprite->getTexture()->getPixelsHigh();
	gs->camera->addChild(sprite);
}


EnemyScout::~EnemyScout()
{
}

void EnemyScout::update(float dt)
{
	lastShot++;
	dx = (gs->player->x - x);
	dy = (gs->player->y - y);
	float length = sqrt(dx * dx + dy * dy);
	if (length < 10)
	{
		dx = 0;
		dy = 0;
	}
	else if(length < visibilityRange)
	{
		/*float angle = CC_RADIANS_TO_DEGREES(atan2(-dy, dx));
		// TODO Check visibility
		shoot(angle);*/
		// Normalizing delta's and applying speed
		dx *= speed / length;
		dy *= speed / length;
	}
	else
	{
		dx = 0;
		dy = 0;
	}

	x_axis = true;
	y_axis = true;
}

void EnemyScout::shoot(float rotation)
{
	if (lastShot >= fireRate)
	{
		gs->addEntity(new Bullet(gs, this, cosf(CC_DEGREES_TO_RADIANS(rotation)) * 24, -sinf(CC_DEGREES_TO_RADIANS(rotation)) * 24));
		lastShot = 0;
	}
}

void EnemyScout::destroy()
{
	gs->camera->removeChild(sprite, true);
}

void EnemyScout::setPositionX(float x)
{
	this->x = x;
	sprite->setPositionX(x);
}

void EnemyScout::setPositionY(float y)
{
	this->y = y;
	sprite->setPositionY(y);
}
