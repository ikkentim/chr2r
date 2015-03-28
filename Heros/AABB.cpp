#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(Vector2 center, Vector2 halfDimension)
{
	center_ = center;
	halfDimension_ = halfDimension;
}

bool AABB::contains_point(Vector2 position)
{
	bool tmp = !(center_.x - halfDimension_.x > position.x ||
		center_.x + halfDimension_.x < position.x ||
		center_.y - halfDimension_.y > position.y ||
		center_.y + halfDimension_.y < position.y);

	return tmp;
}

bool AABB::intersects_with(AABB *box)
{
	// PERFORMANCE
	Vector2 boxCenter = box->center();
	Vector2 boxHalfDimension = box->half_dimension();

	bool tmp = !(boxCenter.x - boxHalfDimension.x > center_.x + halfDimension_.x
		|| boxCenter.x + boxHalfDimension.x < center_.x - halfDimension_.x
		|| boxCenter.y - boxHalfDimension.y > center_.y + halfDimension_.y
		|| boxCenter.y + boxHalfDimension.y < center_.y - halfDimension_.y);

	return tmp;
}