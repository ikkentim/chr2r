#pragma once

#include "Vector2.h"
#include <Windows.h>
#include "Keys.h"
class HUD {
public:
    virtual void Update(class GameScene *, double, Keys) = 0;
    virtual void Render(HDC) = 0;
};