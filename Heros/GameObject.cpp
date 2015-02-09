#include "GameObject.h"
#include "Rectangle.h"
#include <algorithm>

GameObject::GameObject() :position_({}), velocity_({}) {

}
GameObject::GameObject(Vector2 pos, Vector2 size) : position_(pos), size_(size), velocity_({}) {

}

bool GameObject::FixCollider(GameObject *object, Vector2 &overlapping)
{
	// if this object's velocity is 0,0. The other object is the problem so that one has to fix it
	if (this->Velocity() == Vector2(0, 0))
		return true;

	bool x = true;
	bool y = true;

	if (CheckCollidingVelocity(this, object, x, y))
	{
        double max = std::max(this->Velocity().x, this->Velocity().y) + 1;

        double xMinus = (Velocity().x / max * 2) * -1;
        double yMinus = (Velocity().y / max * 2) * -1;

		for (int i = 0; i < max; i++)
		{
			if (y)
			{
				overlapping.y += yMinus;
				velocity_.y += yMinus;
			}

			if (x)
			{
				overlapping.x += xMinus;
				velocity_.x += xMinus;
			}


			if (!CheckCollidingVelocity(this, object, x, y))
				return false;
		}
	}

	return true;
}

bool GameObject::CheckCollidingVelocity(GameObject *go1, GameObject *go2, bool &x, bool &y)
{
	x = false;
	y = false;

	if (!IsIntersecting(go1, go2))
		return false;
	
	// keep a backup of the original velocity because we're changing them for detection
	Vector2 oldVelocity = velocity_;
	
	// check if we set velocity x to 0 if the collision is fixed, this proves that x is (part of) the problem
	velocity_.x = 0;
	if (!IsIntersecting(go1, go2))
		x = true;
	velocity_.x = oldVelocity.x;

	// check if we set velocity y to 0 if the collision is fixed, this proves that y is (part of) the problem
	velocity_.y = 0;
	if (!IsIntersecting(go1, go2))
		y = true;
	velocity_.y = oldVelocity.y;

	return true;
}

bool GameObject::IsIntersecting(GameObject * go1, GameObject * go2)
{
	return !(go1->Position().x + go1->Velocity().x >= go2->Position().x + go2->Size().x
		|| go1->Position().x + go1->Size().x + go1->Velocity().x <= go2->Position().x
		|| go1->Position().y + go1->Velocity().y >= go2->Position().y + go2->Size().y
		|| go1->Position().y + go1->Size().y + go1->Velocity().y <= go2->Position().y);
}

bool GameObject::InRange(GameObject *go, double range)
{
    double actualRange = sqrt(pow((position_.x - go->Position().x), 2) + pow((position_.y - go->Position().y), 2));

	return (actualRange <= range);
}

void GameObject::ApplyVelocity(double delta)
{
	position_ += velocity_;
}

void GameObject::EnteredCollision(GameObject *collider, Vector2 &overlapped)
{
	
}