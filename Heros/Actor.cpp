#include "Actor.h"
#include <Windows.h>

#define GRAVITY             (981.0)

Actor::Actor() :GameObject(){

}

Actor::Actor(Vector2 pos, Vector2 size) :GameObject(pos, size) {}

void Actor::Falling( double delta){
    if (!IsOnGround())
        velocity_ += (Vector2(0, GRAVITY) * delta);
}