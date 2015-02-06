#include "Actor.h"

#pragma once

class Player : public Actor {
public:
    Player(Vector2 position, Vector2 size);
    void Update(float, Keys);
	void Render();
	virtual void EnteredCollision(GameObject *, Vector2 &);
};