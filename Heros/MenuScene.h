#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

class MenuScene : public Scene {
public:
	MenuScene(GameWindow *);
    ~MenuScene() override;
    void start() override;
    void update(double, Keys) override;
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