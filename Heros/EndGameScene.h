/**
 * EndGameScene.h
 * Declares the EndGameScene class.
 */
#pragma once

#include "IScene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

// Represents an end-game scene
class EndGameScene : public IScene {
public:
    // A constructor which sets the gamewindow
    EndGameScene(GameWindow *window);

    // Default destructor
    ~EndGameScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

private:
    SpriteSheet *spriteSheet_;
    double position_;
    GameWindow *window_;
};