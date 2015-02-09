#pragma once

#include <vector>

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
private:
    LevelLayer backgroundLayer_;
    LevelLayer playableLayer_;
    LevelLayer foregroundLayer_;
};