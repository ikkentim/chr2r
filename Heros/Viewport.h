#pragma once

#include "Vector2.h"

struct Viewport {
	int x;
	int y;
	int width;
    int height;

    Viewport(int a, int b, int w, int h) 
        :x(a), y(b), width(w), height(h) {
    }

	inline Vector2 position() {
        return{ (double)x, (double)y };
	}

    inline Vector2 size() {
        return{ (double)width, (double)height };
    }
};