#pragma once

#include "HUD.h"

class TestHUD : public HUD {
public:
	int lives_;
    void Update(GameScene *, double, Keys);
    void Render(HDC);
};