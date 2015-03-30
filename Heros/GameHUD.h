#pragma once

#include "HUD.h"
#include "GameScene.h"

class GameHUD : public HUD {
public:
	int lives_ = 0;
    void update(GameScene *, double, Keys);
    void render(HDC);
};