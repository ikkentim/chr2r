#pragma once

#include "Vector2.h"
#include "GameObject.h"

class AABB {
public:
	AABB();
	AABB(Vector2, Vector2);
	bool contains_point(Vector2);
	bool intersects_with(AABB*);
	Vector2 center()
	{
		return center_;
	}
	Vector2 half_dimension()
	{
		return halfDimension_;
	}
private:
	Vector2 center_;
	Vector2 halfDimension_;
};