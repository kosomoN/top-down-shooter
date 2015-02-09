#include "GameState.h"

GameState::~GameState()
{
}

void GameState::addEntity(Entity *entity)
{
	entities.push_back(entity);
}