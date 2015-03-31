#pragma once

#include "Vector2.h"
#include "GameObject.h"

struct AABB {
    Vector2 center;
    Vector2 half_dimension;

    AABB() { }

    AABB(Vector2 c, Vector2 h) {
        center = c;
        half_dimension = h;
    }

    bool contains_point(Vector2 position) {
        bool tmp = !(center.x - half_dimension.x > position.x ||
            center.x + half_dimension.x < position.x ||
            center.y - half_dimension.y > position.y ||
            center.y + half_dimension.y < position.y);

        return tmp;
    }

    bool intersects_with(AABB box) {
        return !(box.center.x - box.half_dimension.x > center.x + half_dimension.x
            || box.center.x + box.half_dimension.x < center.x - half_dimension.x
            || box.center.y - box.half_dimension.y > center.y + half_dimension.y
            || box.center.y + box.half_dimension.y < center.y - half_dimension.y);
    }
};