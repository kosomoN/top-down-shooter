#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "cocos2d.h"

using namespace cocos2d;

class GameOverState : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameOverState)
}

#endif
