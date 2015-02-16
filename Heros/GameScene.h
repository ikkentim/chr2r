#pragma once

#include <irrKlang.h>
#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    virtual ~GameScene();
	virtual void Start();
    void Update(double, Keys);
    void Render(double);
    irrklang::ISoundEngine *SoundEngine() {
        return window_->SoundEngine();
    }
private:
    GameWindow *window_;
    Player *player_;
    LevelManager *level_;
    Viewport viewport_;
};