/**
 * SplashScene.h
 * Declares the SplashScene class.
 */
#pragma once

#include "IScene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

// Represents a splash screen
class SplashScene : public IScene {
public:
    // A constructor which sets the gamewindow
    SplashScene(GameWindow *window);

    // Default destructor
    ~SplashScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

private:
    SpriteSheet *spriteSheet_;
    double time_;
    GameWindow *window_;
};