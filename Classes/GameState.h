#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "cocos2d.h"
class Camera2d;
class Player;
class Entity;
class Bullet;

using namespace cocos2d;

class GameState : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameState);

	Node *camera;
	TMXObjectGroup* mapHitboxes;
	Player *player;
	float mouseX = 0, mouseY = 0;
	bool mouseDown = false;

	void update(float dt);
	void addEntity(Entity *entity);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *e);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *e);
	void onMouseDown(Event *e);
	void onMouseUp(Event *e);
	void onMouseMove(Event *e);
	bool isKeyDown(EventKeyboard::KeyCode keyCode);
	Player *getPlayer() { return player; }
private:
	TMXTiledMap *map;
	std::vector<Entity*> entities;
	std::vector<Bullet*> bullets;
	std::vector<EventKeyboard::KeyCode> keysDown;
};
#endif
