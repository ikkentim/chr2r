#include "Actor.h"

#pragma once

class Player : public Actor {
public:
    Player(Vector2);
    void Update(float, Keys);
    void Render(Viewport &);
};