#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "cocos2d.h"
#include "Player.h"
#include "Entity.h"

using namespace cocos2d;

class GameState : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameState);

	void update(float dt);
	void addEntity(Entity *entity);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *e);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *e);
	bool isKeyDown(EventKeyboard::KeyCode keyCode);
private:
	Player *player;
	std::vector<Entity*> entities;
	std::vector<EventKeyboard::KeyCode> keysDown;
};
#endif
