#ifndef STATE_H
#define STATE_H

#include "cocos2d.h"

class State
{
public:
	State();
	~State();

	cocos2d::Scene* getScene();
	cocos2d::Scene *scene;
};
#endif