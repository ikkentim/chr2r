#pragma once

#include "GameObject.h"

class Actor : public GameObject {
public:
	enum State {
		ALIVE,
		DEAD,
		JUMPING,
		FALLING,
		MOVING
	};

    Actor();
    void Falling(double delta);
	Actor(Vector2 position, Vector2 size);
	virtual void SetState(State);
	virtual State GetState();
protected:
	State state_;
};