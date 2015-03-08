#pragma once

#include <irrKlang.h>
#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"
#include <vector>

typedef std::vector <class HUD *> HUDVector;

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    virtual ~GameScene();
	virtual void Start();
    void Update(double, Keys);
    void Render(double, HDC graphics);
    irrklang::ISoundEngine *SoundEngine() {
        return window_->SoundEngine();
    }
    Player *player() {
        return player_;
    }
    LevelManager *level() {
        return level_;
    }

	enum State {
		PLAYING,
		PLAYER_DEAD,
		REACHED_END,
		PAUSED
	};
private:
    GameWindow *window_;
    Player *player_;
    HUDVector *hud_;
    LevelManager *level_;
    Viewport viewport_;
	void UpdateViewport();
	bool CheckStates();
	void SetState();
	State GetState();
	State state_;
};