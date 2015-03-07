#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "cocos2d.h"

using namespace cocos2d;

class MainMenuState : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuState);
};

#endif
