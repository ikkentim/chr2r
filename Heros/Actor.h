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
	Actor(Vector2 position, Vector2 size);

    void process_gravity(double delta);
	virtual void state(State);
    virtual State state();
protected:
	State state_;
};