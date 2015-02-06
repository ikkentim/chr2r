#include "GameObject.h"
#include "Rectangle.h"

GameObject::GameObject() :position_({}) {

}
GameObject::GameObject(Vector2 pos, Vector2 size) : position_(pos), size_(size) {

}

bool GameObject::CollidesWith(GameObject *object, Vector2 &overlapping)
{
	if (this->position_.x >= object->position_.x + object->size_.x
		|| this->position_.x + this->size_.x <= object->position_.x
		|| this->position_.y >= object->position_.y + object->size_.y
		|| this->position_.y + this->size_.y <= object->position_.y)
		// rectangles are out of each other
		return false;

	// there is a collision, calculate the factor to unstuck

	Vector2 base = Vector2(this->position_.x, this->position_.y) * -1;

	Vector2 bottomRight1 = Vector2(this->position_.x + this->size_.x, this->position_.y + this->size_.y) + base;
	Vector2 bottomRight2 = Vector2(object->position_.x + object->size_.x, object->position_.y + object->size_.y) + base;

	overlapping = bottomRight2 - bottomRight1; // vector to applied to object to unstuck it.
	
	
	overlapping.y = 0 - (overlapping.y - this->size_.y);
	
	overlapping = overlapping * -1;

	if (overlapping.x > overlapping.y)
		overlapping.x = 0;
	else
		overlapping.y = 0;

	//overlapping.y = this->size_.y + overlapping.y;

	return true;
}

void GameObject::EnteredCollision(GameObject *collider, Vector2 &overlapped)
{
	
}