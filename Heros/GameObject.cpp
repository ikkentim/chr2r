#include "GameObject.h"
#include "Rectangle.h"
#include <algorithm>
#include <vector>
#include <Windows.h>


GameObject::GameObject() 
    :position_({}), velocity_({}) {
}

GameObject::GameObject(bool isMovable) 
    :isMovable_(isMovable), position_({}), velocity_({}) {
}

GameObject::GameObject(Vector2 pos, Vector2 size) 
    :position_(pos), size_(size), velocity_({}) {
}

GameObject::GameObject(bool isMovable, Vector2 pos, Vector2 size) 
    :isMovable_(isMovable), position_(pos), size_(size), velocity_({}) {
}

void GameObject::ApplyVelocity(double delta) {
	position_ += velocity_ * delta;
}

bool GameObject::IsCollidingWith(GameObject *other, double delta) {
    Vector2 position = position_ + velocity_ * delta;

    /* FIXME: Take velocity into account? */
    Vector2 other_position = other->position_;

    /* TODO: Optimalisations. */
    double maxy1 = position.y + size_.y / 2;
    double maxy2 = other_position.y + other->size_.y / 2;

    double miny1 = position.y - size_.y / 2;
    double miny2 = other_position.y - other->size_.y / 2;

    double maxx1 = position.x + size_.x / 2;
    double maxx2 = other_position.x + other->size_.x / 2;

    double minx1 = position.x - size_.x / 2;
    double minx2 = other_position.x - other->size_.x / 2;

    return !(minx1 >= maxx2 || maxx1 <= minx2 ||
        miny1 >= maxy2 || maxy1 <= miny2);
}

void GameObject::CheckForCollisions(LevelLayer *layer, double delta) {
    bool has_touched_ground = false;

    for (LevelLayer::iterator iter = layer->begin(); 
        iter != layer->end(); ++iter) {
        GameObject *check = *iter;

        /* Don't check collision with yourself or objects that are twice your size + velocity away. */
		if (this == check || !InRange(check, max(size_.x + velocity_.x, size_.y + velocity_.y) * 2)) {
            continue;
        }

        if (IsCollidingWith(check, delta)) {
            /* notify children. */
            EnteredCollision(check);

            Vector2 offset_before = position_ - check->position_;
            Vector2 offset_prevented = position_ + velocity_ * delta - 
                check->position_;

            double min_distance_x = (size_.x + check->size_.x) / 2;
            double min_distance_y = (size_.y + check->size_.y) / 2;

            if (abs((offset_before.x) / min_distance_x) >
                abs((offset_before.y) / min_distance_y)) {
                /* Move X axis to free worldspace. */
                position_.x = offset_before.x < 0
                    ? check->position_.x - min_distance_x
                    : check->position_.x + min_distance_x;

                /* FIXME: if x is fractionally colliding, do not modify velocity. */
                // velocity_.x = 0;
            }
            else {
                has_touched_ground = has_touched_ground || offset_before.y < 0;
                /* Move Y axis to free worldspace. */
                position_.y = offset_before.y < 0
                    ? check->position_.y - min_distance_y
                    : check->position_.y + min_distance_y;

                velocity_.y = 0;
            }
        }
    }

    onGround_ = has_touched_ground;
}

double GameObject::Range(GameObject * object)
{
	return sqrt(pow(position_.x - object->Position().x, 2) + pow(position_.y - object->Position().y, 2));
}

bool GameObject::InRange(GameObject * object, int range)
{
	return Range(object) < range;
}

void GameObject::EnteredCollision(GameObject *collider) {
	
}