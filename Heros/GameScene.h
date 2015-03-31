/**
 * GameScene.h
 * Declares the GameScene class.
 */
#pragma once

#include <irrKlang.h>
#include "DialogHUD.h"
#include "IScene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"
#include <vector>
#include "Character.h"
#include "QuadTree.h"

class DialogHUD;
typedef std::vector <class IHUD *> HUDVector;

// Represents a game scene
class GameScene : public IScene {
public:
	enum State {
		PLAYING,
		PLAYER_DEAD,
		REACHED_END,
		PAUSED,
		TALKING
	};

    // A constructor which sets the window
    GameScene(GameWindow *window);

    // Default destructor
    ~GameScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

    // Gets the sound engine
    irrklang::ISoundEngine *sound_engine() {
        return window_->sound_engine();
    }

    // Gets the player
    Player *player() {
        return player_;
    }

    // Gets the level
	LevelManager *level() {
        return level_;
    }

    // Gets the window
    GameWindow *window() {
        return window_;
    }

    // Gets the state
	void state(State);

    // Sets the state
    State state();

    // Loads the specified level
    void load_level(const char * path);

    // Unloads the loaded level
    void unload_level();

    /* TODO: make private */
    // The dialgue element
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