#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"
class EndGameScene : public Scene {
public:
    EndGameScene(GameWindow *);
    virtual ~EndGameScene();
    virtual void Start();
    void Update(double, Keys);
    void Render(HDC graphics);
private:
    SpriteSheet *spriteSheet_;
    double time_;
    GameWindow *window_;
};