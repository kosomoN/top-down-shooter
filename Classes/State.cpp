#include "State.h"

State::State()
{
	scene = cocos2d::Scene::create();
	scene->schedule(schedule_selector(State::render), 1.0f);
}

State::~State()
{
}

void State::enter() {}
void State::exit() {}
void State::render(float dt) {}

cocos2d::Scene* State::getScene()
{
	return State::scene;
}
