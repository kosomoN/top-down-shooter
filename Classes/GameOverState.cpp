#include "GameOverState.h"

USING_NS_CC;

Scene* GameOverState::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverState::create();
	scene->add(layer);
	return scene;
}

bool GameOverState::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	return true;
}
