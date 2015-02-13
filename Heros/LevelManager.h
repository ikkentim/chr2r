#pragma once

#include <vector>
#include "Texture.h"
#include "SpriteSheet.h"
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
	enum Layer : char { MOVABLE, BACKGROUND, PLAYABLE, FOREGROUND };
	void Add(GameObject *, LevelManager::Layer);

    static LevelManager *Load(const char *, class GameScene *, class Player *&);
    static void WriteSimpleLevel();/* TODO: TEMP! Delete soon! */
private:
    LevelLayer backgroundLayer_;
    LevelLayer playableLayer_;
    LevelLayer foregroundLayer_;
	LevelLayer movables_;
};