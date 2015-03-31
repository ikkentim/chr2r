/**
 * ObjectData.h
 * Defines the ObjectData structure.
 */
#pragma once

#include "LevelManager.h"
#include "ObjectType.h"

// Contains object data
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