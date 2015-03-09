#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(Vector2 center, Vector2 halfDimension)
{
	center_ = center;
	halfDimension_ = halfDimension;
}

bool AABB::ContainsPoint(GameObject* gameObject)
{
	Vector2 position = gameObject->Position();

	bool tmp = !(center_.x - halfDimension_.x > position.x ||
		center_.x + halfDimension_.x < position.x ||
		center_.y - halfDimension_.y > position.y ||
		center_.y + halfDimension_.y < position.y);

	return tmp;
}

bool AABB::IntersectsWith(AABB *box)
{
	// PERFORMANCE
	Vector2 boxCenter = box->Center();
	Vector2 boxHalfDimension = box->HalfDimension();
	Vector2 center = Center();
	Vector2 halfDimension = HalfDimension();

	bool tmp = !(boxCenter.x - boxHalfDimension.x > center.x + halfDimension.x
		|| boxCenter.x + boxHalfDimension.x < center.x - halfDimension.x
		|| boxCenter.y - boxHalfDimension.y > center.y + halfDimension.y
		|| boxCenter.y + boxHalfDimension.y < center.y - halfDimension.y);

	return tmp;
}