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
	enum State {
		PLAYING,
		PLAYER_DEAD,
		REACHED_END,
		PAUSED,
		TALKING
	};
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
    GameWindow *window() {
        return window_;
    }
	void state(State);
    State state();

    void load_level(const char * path);
    void unload_level();

    /* TODO: make private */
	DialogHUD *dialog_;
private:
	void update_viewport();
	bool check_states();

	GameWindow *window_ = NULL;
    Player *player_ = NULL;
    HUDVector hud_;
    LevelManager *level_ = NULL;
    Viewport viewport_;
    State state_ = PLAYING;
	bool pausePressed_ = true;
	GameObject* collisionBuffer_[500];
	QuadTree *quadTree_;
    char lastLevelPath_[MAX_LEVEL_PATH];
};