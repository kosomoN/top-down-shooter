#include "GameState.h"

USING_NS_CC;

Scene* GameState::createScene()
{
	auto scene = Scene::create();
	auto layer = GameState::create();
	scene->addChild(layer);
	return scene;
}

bool GameState::init()
{
	if (!Layer::init())
	{
		return false;
	}

	player = new Player(this, Vec2(250, 200));

	// Add input handling
	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = CC_CALLBACK_2(GameState::onKeyPressed, this);
	keyboard->onKeyReleased = CC_CALLBACK_2(GameState::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);


	// Add update method to schedule with some interval in seconds
	this->schedule(schedule_selector(GameState::update), 1.0f / 60);

	return true;
}

void GameState::update(float dt)
{
	player->update(dt);
}

void GameState::addEntity(Entity *entity)
{
	entities.push_back(entity);
}

void GameState::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *e)
{
	// Add keycode to list if it doesn't already contain it
	if (!isKeyDown(keyCode))
		keysDown.push_back(keyCode);
}

void GameState::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *e)
{
	// Remove keycode from list
	keysDown.erase(std::remove(keysDown.begin(), keysDown.end(), keyCode), keysDown.end());
}

bool GameState::isKeyDown(EventKeyboard::KeyCode keyCode)
{
	return std::find(keysDown.begin(), keysDown.end(), keyCode) != keysDown.end();
}