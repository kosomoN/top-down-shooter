#include "GameState.h"
#include "Entity.h"
#include "Physics.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyScout.h"
#include "Wall.h"
#include "AppDelegate.h"

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

	// Load map from .tmx
	map = TMXTiledMap::create("Map1.tmx");
	mapHitboxes = map->getObjectGroup("Walls");

	camera = Node::create();
	camera->setPosition(Vec2(0, 0));
	camera->addChild(map);

	physics = new Physics(this);

	reset();
	
	// Add camera node to layer
	addChild(camera);

	// Add input handling
	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = CC_CALLBACK_2(GameState::onKeyPressed, this);
	keyboard->onKeyReleased = CC_CALLBACK_2(GameState::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	auto mouse = EventListenerMouse::create();
	mouse->onMouseDown = CC_CALLBACK_1(GameState::onMouseDown, this);
	mouse->onMouseMove = CC_CALLBACK_1(GameState::onMouseMove, this);
	mouse->onMouseUp = CC_CALLBACK_1(GameState::onMouseUp, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse, this);

	// Add update method to schedule with some interval in seconds
	this->schedule(schedule_selector(GameState::update), 1.0f / 60);

	return true;
}

void GameState::update(float dt)
{
	// Update each entity
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->update(dt);
	}

	physics->update();

	// Camera origin is lower left, 5.0f came through testing
	camera->setPositionX(-(player->x + player->distX / 5.0f - 960 / 2));
	camera->setPositionY(-(player->y - player->distY / 5.0f - 640 / 2));
}

void GameState::reset()
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->destroy();
	}
	entities.clear();

	// Add walls as entities
	for (unsigned int i = 0; i < mapHitboxes->getObjects().size(); i++)
	{
		ValueMap valMap = mapHitboxes->getObjects().at(i).asValueMap();
		addEntity(new Wall(
			valMap["x"].asFloat() + valMap["width"].asFloat() / 2.0f,
			valMap["y"].asFloat() + valMap["height"].asFloat() / 2.0f,
			valMap["width"].asFloat(), valMap["height"].asFloat()));
	}

	player = new Player(this, 500, 500);
	addEntity(player);

	// Add a test enemy scout
	addEntity(new EnemyScout(this, 100, 100));
}

void GameState::addEntity(Entity *entity)
{
	entities.push_back(entity);
}

void GameState::removeEntity(Entity *entity)
{
	entity->destroy();
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
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

void GameState::onMouseDown(Event *e)
{
	mouseDown = true;
}

void GameState::onMouseUp(Event *e)
{
	mouseDown = false;
}

void GameState::onMouseMove(Event *e)
{
	Size window = Director::getInstance()->getWinSizeInPixels();
	EventMouse *mouseEvent = dynamic_cast<EventMouse*>(e);
	mouseX = mouseEvent->getCursorX();
	mouseY = mouseEvent->getCursorY() + window.height;
}

bool GameState::isKeyDown(EventKeyboard::KeyCode keyCode)
{
	return std::find(keysDown.begin(), keysDown.end(), keyCode) != keysDown.end();
}
