/**
 * Actor.h
 * Declares the abstract Actor class.
 */
#pragma once

#include "GameObject.h"

// Contains method declarations and methods for an actor.
class Actor : public GameObject {
public:
    // Contains an enumeration of actor states.
	enum State {
		ALIVE,
		DEAD,
		JUMPING,
		FALLING,
		MOVING
	};

    // Default constructor
    Actor();

    // A constructor which sets the position and size of the actor
	Actor(Vector2 position, Vector2 size);

    // Processes the gravity with the specified delta time
    void process_gravity(double delta);

    // Sets the current state
    void state(State value);

    // Gets the current state
    State state();
private:
	State state_;
};