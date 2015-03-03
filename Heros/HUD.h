#pragma once

#include "Vector2.h"
#include "GameScene.h"

class HUD {
public:
    virtual void Update(GameScene *, double, Keys) = 0;
    virtual void Render(HDC) = 0;
};