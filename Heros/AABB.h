#pragma once

#include "Vector2.h"
#include "GameObject.h"

class AABB {
public:
	AABB();
	AABB(Vector2, Vector2);
	bool ContainsPoint(GameObject*);
	bool IntersectsWith(AABB*);
	Vector2 Center()
	{
		return center_;
	}
	Vector2 HalfDimension()
	{
		return halfDimension_;
	}
private:
	Vector2 center_;
	Vector2 halfDimension_;
};