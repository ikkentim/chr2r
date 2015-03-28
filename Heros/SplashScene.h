#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"
class SplashScene : public Scene {
public:
    SplashScene(GameWindow *);
    ~SplashScene() override;
    void start() override;
    void update(double, Keys) override;
    void render(HDC graphics) override;

private:
    SpriteSheet *spriteSheet_;
    double time_;
    GameWindow *window_;
};