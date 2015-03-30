#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"
class EndGameScene : public Scene {
public:
    EndGameScene(GameWindow *);
    ~EndGameScene() override;
    void start() override;
    void update(double, Keys) override;
    void render(HDC graphics) override;

private:
    SpriteSheet *spriteSheet_;
    double position_;
    GameWindow *window_;
};