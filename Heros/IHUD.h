/**
 * IHUD.h
 * Defines the HUD interface.
 */
#pragma once

#include "Vector2.h"
#include <Windows.h>
#include "Keys.h"

class IHUD {
public:
    // Performs the update logic
    virtual void update(class GameScene *, double, Keys) = 0;

    // Renders the graphics
    virtual void render(HDC) = 0;
};