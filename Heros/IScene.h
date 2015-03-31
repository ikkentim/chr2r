/**
 * IScene.h
 * Defines the abstract IScene interface.
 */
#pragma once

#include <Windows.h>
#include "Keys.h"

// Contains method declarations for a scene
class IScene {
public:
    // Default destructor
    virtual ~IScene(){}

    // Initialises the scene
    virtual void start() = 0;

    // Performs the update logic
    virtual void update(double, Keys) = 0;

    // Renders the graphics
    virtual void render(HDC graphics) = 0;
};