/**
 * LevelManager.h
 * Declares the LevelManager class.
 */
#pragma once

#include <vector>
#include "Texture.h"
#include "SpriteSheet.h"
#include "LevelHeader.h"

typedef std::vector <class GameObject *> LevelLayer;

// Represents a level manager
class LevelManager {
public:
    // Contains every available layer
    enum Layer : char 
    { 
        MOVABLE, 
        BACKGROUND, 
        PLAYABLE, 
        FOREGROUND 
    };
    // Default constructor
    LevelManager();

    // Default destructor
    ~LevelManager();

    // Gets the background layer
    LevelLayer *background_layer() {
        return &backgroundLayer_;
    }

    // Gets the playable layer
    LevelLayer *playable_layer() {
        return &playableLayer_;
    }

    // Gets the foreground layer
    LevelLayer *foreground_layer() {
        return &foregroundLayer_;
    }

    // Gets the movables layer
	LevelLayer *movables() {
		return &movables_;
	}

    // Gets the spritesheet for the background
    SpriteSheet *background() {
        return background_;
    }

    // Gets the spritesheet for the background overlay
    SpriteSheet *background_overlay() {
        return backgroundOverlay_;
    }

    // Gets the background width
    int background_width() {
        return backgroundWidth_;
    }

    // Gets the background overlay width
    int background_overlay_width() {
        return backgroundOverlayWidth_;
    }

    // Gets the bottom y coordinate under which the player dies
    int bottom_y() {
        return bottomY_;
    }

    // Gets the x coordinate the player needs to pass to win
    int end_game_x() {
        return endGameX_;
    }

    // Gets a value indicating whether the finish is right of the player spawn
    bool is_end_game_right() {
        return isEndGameRight_;
    }

    // Gets a value indicating whether this is the last level
    bool is_last_level() {
        return strlen(nextLevel_) == 0;
    }

    // Gets the path to the next level
    char *next_level() {
        return nextLevel_;
    }

    // Gets the path to the background music
    char *sound() {
        return sound_;
    }

    // Adds the specified object to the specified layer
	void add(GameObject *object, LevelManager::Layer layer);

    // Loads the specified file
    static LevelManager *load(const char *path, class GameScene *scene, 
        class Player *&player);

private:
    int backgroundWidth_;
    int backgroundOverlayWidth_;
    int bottomY_;
    int endGameX_;
    char nextLevel_[MAX_LEVEL_PATH];
    char sound_[MAX_SOUND_NAME];
    bool isEndGameRight_;

    SpriteSheet *background_ = NULL;
    SpriteSheet *backgroundOverlay_ = NULL;
    LevelLayer backgroundLayer_;
    LevelLayer playableLayer_;
    LevelLayer foregroundLayer_;
	LevelLayer movables_;
};