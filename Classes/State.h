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

	virtual void enter();
	virtual void exit();
	virtual void render(float dt);
};
#endif