#include "State.h"

State::State()
{
	scene = cocos2d::Scene::create();
}

State::~State()
{
}

cocos2d::Scene* State::getScene()
{
	return State::scene;
}
