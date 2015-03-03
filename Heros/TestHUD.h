#pragma once

#include "HUD.h"

class TestHUD : public HUD {
public:
    void Update(GameScene *, double, Keys);
    void Render(HDC);
};