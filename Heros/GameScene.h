#pragma once

#include <irrKlang.h>
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
    irrklang::ISoundEngine *SoundEngine() {
        return window_->SoundEngine();
    }
private:
    GameWindow *window_;
    LevelManager *level_;
    Player *player_;
    Viewport viewport_;
    Ennemis *ennemis_;
};