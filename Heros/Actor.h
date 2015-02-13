#pragma once

#include "GameObject.h"

class Actor : public GameObject {
public:
    Actor();
    Actor(Vector2);
    void Falling(double delta);
	Actor(Vector2 position, Vector2 size);
protected:
};