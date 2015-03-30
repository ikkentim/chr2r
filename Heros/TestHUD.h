#pragma once

#include "HUD.h"

class TestHUD : public HUD {
public:
	int lives_;
    void update(GameScene *, double, Keys);
    void render(HDC);
};