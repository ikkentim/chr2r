/**
 * AABB.h
 * Defines the AABB structure.
 */
#pragma once

#include "Vector2.h"
#include "GameObject.h"

// Represents an axis aligned bounding box
struct AABB {
    // The center point
    Vector2 center;

    // Half the size of the box
    Vector2 half_dimension;

    // Default constructor
    AABB() { }

    // A constructor which sets the center and half dimension
    AABB(Vector2 _center, Vector2 _half_dimension) {
        center = _center;
        half_dimension = _half_dimension;
    }

    // Gets a value indicating whether the specified position is within the box
    bool contains_point(Vector2 position) {
        bool tmp = !(center.x - half_dimension.x > position.x ||
            center.x + half_dimension.x < position.x ||
            center.y - half_dimension.y > position.y ||
            center.y + half_dimension.y < position.y);

        return tmp;
    }

    // Gets a value indicating whether the specified box intersects with the box
    bool intersects_with(AABB box) {
        return !(box.center.x - box.half_dimension.x > center.x + half_dimension.x
            || box.center.x + box.half_dimension.x < center.x - half_dimension.x
            || box.center.y - box.half_dimension.y > center.y + half_dimension.y
            || box.center.y + box.half_dimension.y < center.y - half_dimension.y);
    }
};