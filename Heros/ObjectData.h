#pragma once

#include "LevelManager.h"

enum ObjectType {
    BLOCK,
    COIN
};


struct ObjectData {
    ObjectData() :texture(Texture(0, 0, 0, 0)) {
    }

    int x;
    int y;
    int width;
    int height;
    Texture texture;
    ObjectType type;
    LevelManager::Layer layer;
};