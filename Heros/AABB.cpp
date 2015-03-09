#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(Vector2 center, Vector2 halfDimension)
{
	center_ = center;
	halfDimension_ = halfDimension;
}

bool AABB::ContainsPoint(GameObject* position)
{
	bool tmp = !(center_.x - halfDimension_.x > position->Position().x ||
		center_.x + halfDimension_.x < position->Position().x ||
		center_.y - halfDimension_.y > position->Position().y ||
		center_.y + halfDimension_.y < position->Position().y);

	return tmp;
}

bool AABB::IntersectsWith(AABB box)
{
	bool tmp = !(box.Center().x - box.HalfDimension().x > Center().x + HalfDimension().x
		|| box.Center().x + box.HalfDimension().x < Center().x - HalfDimension().x
		|| box.Center().y - box.HalfDimension().y > Center().y + HalfDimension().y
		|| box.Center().y + box.HalfDimension().y < Center().y - HalfDimension().y);

	return tmp;
}