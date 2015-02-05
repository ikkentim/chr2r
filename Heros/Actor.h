#include "GameObject.h"

#pragma once

class Actor : public GameObject {
public:
	Actor();
    Actor(Vector2);
	void Falling(Vector2 grav, float delta);
protected:
    Vector2 velocity_;
	bool onGround;
};