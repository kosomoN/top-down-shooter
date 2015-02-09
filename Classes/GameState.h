#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "cocos2d.h"
#include "State.h"
#include "Entity.h"

class GameState : public State
{
public:
	GameState() : State()
	{

	}
	~GameState();

	void addEntity(Entity *entity);
private:
	std::vector<Entity*> entities;
};
#endif
