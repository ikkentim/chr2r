#include "GameObject.h"
#include "Rectangle.h"
#include <algorithm>

GameObject::GameObject() :position_({}), velocity_({}) {

}
GameObject::GameObject(Vector2 pos, Vector2 size) : position_(pos), size_(size), velocity_({}) {

}

bool GameObject::CollidesWith(GameObject *object, Vector2 &overlapping)
{
	bool x = true;
	bool y = true;

	if (IsIntersecting(this, object, x, y))
	{
		const int step = 10;

		float max = std::max(this->Velocity().x, this->Velocity().y);

		float xMinus = (Velocity().x / step) * -1;
		float yMinus = (Velocity().y / step) * -1;

		for (int i = 0; i < step; i++)
		{
			if (x)
				velocity_.x += xMinus;

			if (y)
				velocity_.y += yMinus;

			if (!IsIntersecting(this, object, x, y))
				return false;
		}
	}

	return true; 
//
//	if (this->position_.x + this->velocity_.x >= object->position_.x + object->size_.x
//		|| this->position_.x + this->size_.x + this->velocity_.x <= object->position_.x
//		|| this->position_.y + this->velocity_.y >= object->position_.y + object->size_.y
//		|| this->position_.y + this->size_.y + this->velocity_.y <= object->position_.y)
//		// rectangles are out of each other
//		return false;
//
//	
//	// there is a collision, calculate the factor to unstuck
//
//	Vector2 point1 = Vector2(position_.x + size_.x / 2, position_.y + size_.y / 2);
//	Vector2 point2 = Vector2(object->position_.x + object->size_.x / 2, object->position_.y + object->size_.y / 2);
//
//	float dist = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
//
//	float x = point2.x - point1.x;
//	float y = point2.y - point1.y;
//
//	if (y < size_.y)
//		velocity_.y = y - size_.y;
//
//	if (x < size_.x)
//		velocity_.x = x - size_.x;
//	else if (x > size_.x)
//		velocity_.x = x * -1 + size_.x;
///*
//	int z = atan2(y * -1, x);
//
//	if (z < 0)
//		z += (float)2 * 3.14159265358979323846;
//
//	z = z * 180 / 3.14159265358979323846;*/
//
//	overlapping = Vector2(x, y);
//
//	/*overlapping = (Vector2(16, 16) - Vector2(x, y)) * -1;
//
//	overlapping.x = 0;*/
//
//	//Vector2 base = Vector2(this->position_.x, this->position_.y) * -1;
//
//	//Vector2 bottomRight1 = Vector2(this->position_.x + this->size_.x, this->position_.y + this->size_.y) + base;
//	//Vector2 bottomRight2 = Vector2(object->position_.x + object->size_.x, object->position_.y + object->size_.y) + base;
//
//	//overlapping = bottomRight2 - bottomRight1; // vector to applied to object to unstuck it.
//
//	//overlapping.y = 0 - (overlapping.y - this->size_.y);
//	//
//	//overlapping = overlapping * -1;
//
//	//float x = abs(overlapping.x);
//	//float y = abs(overlapping.y);
//
//	//if (y > x)
//	//	overlapping.x = 0;
//	//else if (x > y)
//	//	overlapping.y = 0;
//	//else
//	//	overlapping = Vector2(0, 0);
//
//	//overlapping.y = this->size_.y + overlapping.y;
//
//	return true;
}

bool GameObject::IsIntersecting(GameObject *go1, GameObject *go2, bool &x, bool &y)
{
	x = true;
	y = true;

	if (go1->Position().x + go1->Velocity().x >= go2->Position().x + go2->Size().x || go1->Position().x + go1->Size().x + go1->Velocity().x <= go2->Position().x)
		x = false;
	
	if (go1->Position().y + go1->Velocity().y >= go2->Position().y + go2->Size().y || go1->Position().y + go1->Size().y + go1->Velocity().y <= go2->Position().y)
		y = false;

	return (x && y);
}

void GameObject::ApplyVelocity()
{
	position_ += velocity_;
}

void GameObject::EnteredCollision(GameObject *collider, Vector2 &overlapped)
{
	
}