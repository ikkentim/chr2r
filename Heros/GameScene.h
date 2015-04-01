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

    // Adds the specified amount of score
    void add_score(int score);

    // Gets the score
    int score() {
        return score_ + levelScore_;
    }

    // Gets the number of lives left
    int lives() {
        return lives_;
    }

    /* TODO: make private */
    // The dialgue element
	DialogHUD *dialog_;
private:
	void update_viewport();
	bool check_states();

    int score_ = 0;
    int lives_ = 3;
    int levelScore_ = 0;
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