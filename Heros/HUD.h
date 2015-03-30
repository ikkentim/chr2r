#pragma once

#include "Vector2.h"
#include <Windows.h>
#include "Keys.h"
class HUD {
public:
    virtual void update(class GameScene *, double, Keys) = 0;
    virtual void render(HDC) = 0;
};