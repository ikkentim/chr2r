#pragma once

#include <vector>
#include "Texture.h"
#include "SpriteSheet.h"
#include "LevelHeader.h"
typedef std::vector <class GameObject *> LevelLayer;

class LevelManager {
public:
    LevelManager();
    ~LevelManager();
    LevelLayer *BackgroundLayer() {
        return &backgroundLayer_;
    }
    LevelLayer *PlayableLayer() {
        return &playableLayer_;
    }
    LevelLayer *ForegroundLayer() {
        return &foregroundLayer_;
    }
	LevelLayer *Movables() {
		return &movables_;
	}
    SpriteSheet *background() {
        return background_;
    }
    SpriteSheet *backgroundOverlay() {
        return backgroundOverlay_;
    }
    int backgroundWidth() {
        return backgroundWidth_;
    }
    int backgroundOverlayWidth() {
        return backgroundOverlayWidth_;
    }
    int bottomY() {
        return bottomY_;
    }
    int endGameX() {
        return endGameX_;
    }
    bool isEndGameRight() {
        return isEndGameRight_;
    }
    bool isLastLevel() {
        return strlen(nextLevel_) == 0;
    }
    char *nextLevel() {
        return nextLevel_;
    }
	enum Layer : char { MOVABLE, BACKGROUND, PLAYABLE, FOREGROUND };
	void Add(GameObject *, LevelManager::Layer);
    static LevelManager *Load(const char *, class GameScene *, class Player *&);
    static void WriteSimpleLevel();/* TODO: TEMP! Delete soon! */
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