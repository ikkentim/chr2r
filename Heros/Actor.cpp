#include "Actor.h"

Actor::Actor() :velocity_({}), GameObject() {

}

Actor::Actor(Vector2 pos) :velocity_({ }), GameObject(pos) {

}