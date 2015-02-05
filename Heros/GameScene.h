#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "Ennemis.h"
#include "GameWindow.h"

#pragma once

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    ~GameScene();
    void Update(float, Keys);
private:
    LevelManager *level_;
    Player *player_;
    Viewport viewport_;
    Ennemis * ennemis_;
};