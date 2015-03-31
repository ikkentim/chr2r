/**
 * Actor.cpp
 * Defines the abstract Actor class.
 */

#include "Actor.h"
#include <Windows.h>

#define GRAVITY             (981.0)

Actor::Actor() :GameObject(){

}

Actor::Actor(Vector2 pos, Vector2 size) :GameObject(pos, size) {}

void Actor::process_gravity(double delta) {
    if (!is_on_ground())
        velocity_ += (Vector2(0, GRAVITY) * delta);
}

void Actor::state(State state) {
	state_ = state;
}

Actor::State Actor::state() {
	return state_;
}