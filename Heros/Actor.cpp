#include "Actor.h"
#include <Windows.h>

Actor::Actor() : GameObject() {}

Actor::Actor(Vector2 pos, Vector2 size) : GameObject(pos, size) {}

void Actor::Falling(Vector2 grav, double delta){
	velocity_ += (grav * delta);
}


void Actor::EnteredCollision(GameObject *object, Vector2 &overlapped)
{
	if (overlapped.y < 0)
		onGround = true;

	//position_ += overlapped;
}