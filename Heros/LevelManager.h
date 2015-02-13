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

    static LevelManager *Load(const char *, class GameScene *, class Player *&);
    static void WriteSimpleLevel();/* TODO: TEMP! Delete soon! */
private:
    LevelLayer backgroundLayer_;
    LevelLayer playableLayer_;
    LevelLayer foregroundLayer_;
};