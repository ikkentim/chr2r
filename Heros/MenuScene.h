/**
 * MenuScene.h
 * Declares the MenuScene class.
 */
#pragma once

#include "IScene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

// Represents a menu scene
class MenuScene : public IScene {
public:

    // A constructor which sets the gamewindow
	MenuScene(GameWindow *window);

    // Default destructor
    ~MenuScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

private:
    SpriteSheet *spriteSheet_;
    SpriteSheet *spriteSheetPlay_;
    SpriteSheet *spriteSheetExit_;
    SpriteSheet *spriteSheetArrow_;
	GameWindow *window_;
	int selectedOption_=0;
	double keyDelay_=0;
};