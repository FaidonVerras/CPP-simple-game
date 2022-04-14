#pragma once
#include "config.h"

class Collidable
{
public:
	virtual Disk getCollisionHull() const = 0;
};

class GameObject
{
public:

	virtual void const draw() = 0;
	virtual bool contains(float x, float y) = 0;
};