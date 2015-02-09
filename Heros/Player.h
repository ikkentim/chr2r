#pragma once

#include "Actor.h"

class Player : public Actor {
public:
    Player(Vector2 position, Vector2 size);
    void Update(double, Keys) override;
    void Render(Viewport &) override;
};