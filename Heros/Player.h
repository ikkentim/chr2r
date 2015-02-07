#include "Actor.h"

#pragma once

class Player : public Actor {
public:
    Player(Vector2 position, Vector2 size);
    void Update(float, Keys);
	virtual void EnteredCollision(GameObject *, Vector2 &);
    void Render(Viewport &);
};