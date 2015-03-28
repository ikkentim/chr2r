#pragma once
#include <irrKlang.h>
#include "DialogHUD.h"
#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"
#include <vector>
#include "Character.h"
#include "QuadTree.h"

class DialogHUD;
typedef std::vector <class HUD *> HUDVector;

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    ~GameScene() override;
    void start() override;
    void update(double, Keys) override;
    void render(HDC graphics) override;
    irrklang::ISoundEngine *sound_engine() {
        return window_->sound_engine();
    }
    Player *player() {
        return player_;
    }
	LevelManager *level() {
        return level_;
    }
	bool paused;
	enum State {
		PLAYING,
		PLAYER_DEAD,
		REACHED_END,
		PAUSED,
		TALKING
	};
	virtual void state(State);
    virtual State state();

	QuadTree *quadTree_;
	DialogHUD *dialog_;

private:
	void update_viewport();
	bool check_states();

	GameWindow *window_;
    Player *player_;
    HUDVector *hud_;
    LevelManager *level_;
    Viewport viewport_;
    State state_ = PLAYING;
	bool pausePressed_ = true;
	GameObject* collisionBuffer_[500];
};