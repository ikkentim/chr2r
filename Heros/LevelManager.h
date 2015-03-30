#pragma once

#include <vector>
#include "Texture.h"
#include "SpriteSheet.h"
#include "LevelHeader.h"
typedef std::vector <class GameObject *> LevelLayer;

class LevelManager {
public:
    enum Layer : char 
    { 
        MOVABLE, 
        BACKGROUND, 
        PLAYABLE, 
        FOREGROUND 
    };

    LevelManager();
    ~LevelManager();

    LevelLayer *background_layer() {
        return &backgroundLayer_;
    }
    LevelLayer *playable_layer() {
        return &playableLayer_;
    }
    LevelLayer *foreground_layer() {
        return &foregroundLayer_;
    }
	LevelLayer *movables() {
		return &movables_;
	}
    SpriteSheet *background() {
        return background_;
    }
    SpriteSheet *background_overlay() {
        return backgroundOverlay_;
    }
    int background_width() {
        return backgroundWidth_;
    }
    int background_overlay_width() {
        return backgroundOverlayWidth_;
    }
    int bottom_y() {
        return bottomY_;
    }
    int end_game_x() {
        return endGameX_;
    }
    bool is_end_game_right() {
        return isEndGameRight_;
    }
    bool is_last_level() {
        return strlen(nextLevel_) == 0;
    }
    char *next_level() {
        return nextLevel_;
    }

	void add(GameObject *, LevelManager::Layer);
    static LevelManager *load(const char *, class GameScene *, class Player *&);

    static void write_simple_level();/* TODO: TEMP! Delete soon! */
private:
    int backgroundWidth_;
    int backgroundOverlayWidth_;
    int bottomY_;
    int endGameX_;
    char nextLevel_[MAX_LEVEL_PATH];
    bool isEndGameRight_;

    SpriteSheet *background_ = NULL;
    SpriteSheet *backgroundOverlay_ = NULL;
    LevelLayer backgroundLayer_;
    LevelLayer playableLayer_;
    LevelLayer foregroundLayer_;
	LevelLayer movables_;
};