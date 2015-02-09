#include "Vector2.h"

#pragma once

struct Viewport {
	int x;
	int y;
	int width;
	int height;
	inline Vector2 Position() {
        return{ (double)x, (double)y };
	}
};