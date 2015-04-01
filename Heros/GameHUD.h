/**
 * GameHUD.h
 * Declares the GameHUD class.
 */
#pragma once

#include "IHUD.h"
#include "GameScene.h"

class GameHUD : public IHUD {
public:

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
    void render(HDC) override;
private:
    int lives_ = 0;
    int score_ = 0;
};