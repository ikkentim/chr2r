#pragma once

#include "Scene.h"
#include "GameWindow.h"

class SplashScene : public Scene {
public:
    SplashScene(GameWindow *);
    virtual ~SplashScene();
	virtual void Start();
    void Update(double, Keys);
    void Render(double);
private:
    double time_;
    GameWindow *window_;
};