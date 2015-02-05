#include "Actor.h"

Actor::Actor() :velocity_({}), GameObject() {}

Actor::Actor(Vector2 pos) :velocity_({ }), GameObject(pos) {}

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