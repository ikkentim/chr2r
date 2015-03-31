/**
 * Viewport.h
 * Defines the Viewport structure.
 */
#pragma once

#include "Vector2.h"

struct Viewport {
    // The X-coordinate
    int x;

    // The Y-coordinate
	int y;

    // The width
	int width;

    // The height
    int height;

    // Constructor which sets the x, y, width and height values
    Viewport(int a, int b, int w, int h) 
        :x(a), y(b), width(w), height(h) {
    }

    // Gets the position
	inline Vector2 position() {
        return{ (double)x, (double)y };
	}

    // Gets the size
    inline Vector2 size() {
        return{ (double)width, (double)height };
    }
};