#include "Actor.h"
#include <Windows.h>

Actor::Actor() :velocity_({}), GameObject() {

}

Actor::Actor(Vector2 pos, Vector2 size) :velocity_({ }), GameObject(pos, size) {

}

void Actor::EnteredCollision(GameObject *object, Vector2 &overlapping)
{
	OutputDebugString("Collision!\n");
}