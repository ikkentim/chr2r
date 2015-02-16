#pragma once

#include <irrKlang.h>
#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    ~GameScene();
    void Update(double, Keys);
    void Render(double);
    irrklang::ISoundEngine *SoundEngine() {
        return window_->SoundEngine();
    }
    Player *player() {
        return player_;
    }
    LevelManager *level() {
        return level_;
    }
private:
    GameWindow *window_;
    Player *player_;
    LevelManager *level_;
    Viewport viewport_;
};