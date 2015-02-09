#include "Actor.h"
#include <Windows.h>

Actor::Actor() :GameObject(true) {
}

Actor::Actor(Vector2 pos, Vector2 size) :GameObject(true, pos, size) {}

void Actor::Falling(Vector2 grav, double delta){
    if (!IsOnGround())
        velocity_ += (grav * delta);
}