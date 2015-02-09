#include "Scene.h"
#include "GameWindow.h"

#pragma once

class SplashScene : public Scene {
public:
    SplashScene(GameWindow *);
    ~SplashScene();
    void Update(double, Keys);
    void Render(double);
private:
    double time_;
    GameWindow *window_;
};