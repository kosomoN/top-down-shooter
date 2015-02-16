#include "Camera2d.h"


Camera2d::Camera2d()
{
	node = Node::create();
}


Camera2d::~Camera2d()
{
}

void Camera2d::addToCamera(Node *n)
{
	node->addChild(n);
}

void Camera2d::move(Vec2 position)
{
	node->setPosition(position);
}
