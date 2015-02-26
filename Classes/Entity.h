#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	virtual void update(float dt) = 0;
	float x, y;
};
#endif