#include "Actor.h"
#include <Windows.h>

Actor::Actor() :velocity_({}), GameObject() {}

Actor::Actor(Vector2 pos, Vector2 size) : velocity_({}), GameObject(pos, size) {}

void Actor::Falling(Vector2 grav, float delta){

	if (!onGround) {
		velocity_ += (grav * delta);
}
	else if (onGround) {
		if (velocity_.y > 2)
			position_.y -= velocity_.y;

		velocity_.y -= velocity_.y;
	}
}


void Actor::EnteredCollision(GameObject *object, Vector2 &overlapping)
{
	OutputDebugString("Collision!\n");
}