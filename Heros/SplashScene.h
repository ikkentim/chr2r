#include "Scene.h"
#include "GameWindow.h"

#pragma once

class SplashScene : public Scene {
public:
    SplashScene(GameWindow *);
    ~SplashScene();
    void Update(float, Keys);
private:
    float time_;
    GameWindow *window_;
};