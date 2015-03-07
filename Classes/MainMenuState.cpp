#include "MainMenuState.h"

USING_NS_CC;

Scene* MainMenuState::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuState::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuState::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	return true;
}
