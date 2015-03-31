/**
 * GameOverScene.h
 * Declares the GameOverScene class.
 */
#pragma once

#include "IScene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

// Represents a game over scene
class GameOverScene : public IScene {
public:
    // A constructor which sets the gamewindow
    GameOverScene(GameWindow *window);

    // Default destructor
    ~GameOverScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

private:
	SpriteSheet *spriteSheet_;
	GameWindow *window_;
	double time_ = 0;
};