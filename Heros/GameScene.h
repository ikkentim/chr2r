#pragma once

#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "Ennemis.h"
#include "GameWindow.h"

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    ~GameScene();
    void Update(double, Keys);
    void Render(double);
private:
    LevelManager *level_;
    Player *player_;
    Viewport viewport_;
    Ennemis * ennemis_;
};