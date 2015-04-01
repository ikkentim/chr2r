/**
 * GameObject.cpp
 * Defines the abstract GameObject class.
 */

#include "GameObject.h"
#include "Rectangle.h"
#include "GameScene.h"
#include <algorithm>
#include <vector>
#include <Windows.h>


GameObject::GameObject() 
    :position_({}), velocity_({}) {
}

GameObject::GameObject(bool isSolid) 
    :isSolid_(isSolid), position_({}), velocity_({}) {
}

GameObject::GameObject(Vector2 pos, Vector2 size) 
    :position_(pos), size_(size), velocity_({}) {
}

GameObject::GameObject(bool isSolid, Vector2 pos, Vector2 size) 
    : isSolid_(isSolid), position_(pos), size_(size), velocity_({}) {
}

void GameObject::apply_velocity(double delta) {
	position_ += velocity_ * delta;
}

bool GameObject::is_colliding_with(GameObject *other, double delta) {
    /* Get the positions of both objects. */
	Vector2 position = position_ + velocity_ * delta;
    Vector2 other_position = other->position_;
	Vector2 other_size = other->size_;

    /* Check whether object is not to the left, 
     * above, right or below this object.
     */
	return !(position.x - size_.x / 2 > other_position.x + other_size.x / 2 ||
		position.x + size_.x / 2 < other_position.x - other_size.x / 2 ||
		position.y - size_.y / 2 > other_position.y + other_size.y / 2 ||
		position.y + size_.y / 2 < other_position.y - other_size.y / 2);
}

//void GameObject::Update(GameScene *, double, Keys){
//	int c = 0;
//}
//void GameObject::Render(Viewport &){
//	int c = 0;
//}

void GameObject::check_for_collisions(GameScene *scene, GameObject** checks, int PossibleColliders, double delta) {
    bool has_touched_ground = false;

	for (int i = 0; i < PossibleColliders; i++)
	{
		GameObject* check = checks[i];
		
        /* Don't check collision with yourself. */
		if (this == check) {
            continue;
        }

        /* If the objects are colliding, take action. */
        if (is_colliding_with(check, delta)) {
            /* Calculate offset between both objects and the offset between 
             * the objects when this objects velocity would be applied. */
            Vector2 offset_before = position_ - check->position_;
            Vector2 offset_prevented = offset_before + velocity_ * delta;

            /* Calculate the collision area. */
            Vector2 collision =
                offset_prevented - (position_ - check->position_);

            /* Calculate the minimum distance required between both objects. */
            double min_distance_x = (size_.x + check->size_.x) / 2;
            double min_distance_y = (size_.y + check->size_.y) / 2;

            /* Find the culprit; the X or Y axis. This can be calculated by
             * finding the RELATIVELY longest axis of the offset between the 
             * objects */
            if (abs((offset_prevented.x) / min_distance_x) >
                abs((offset_prevented.y) / min_distance_y)) {
                /* Notify children. */
                entered_collision(scene, check, collision);
                check->entered_collision(scene, this, -collision);

                /* If not solid, just notify children and don't modify velocity. */
                if (!check->isSolid_) {
                    continue;
                }

                /* Move the X axis to free worldspace. This is done by moving
                 * this object so that there is min_distance_x distance between
                 * the objects on the X axis. */
                position_.x = offset_before.x < 0
                    ? check->position_.x - min_distance_x
                    : check->position_.x + min_distance_x;

                /* If the object is not on the ground, reset the velocity in 
                 * this axis. */
				if (!onGround_)
					velocity_.x = 0;
            }
            else {
                /* Notify children. */
                if (collision.y != 0) {
                    entered_collision(scene, check, collision);
                    check->entered_collision(scene, this, -collision);
                }
                /* If not solid, just notify children and don't modify velocity. */
                if (!check->isSolid_) {
                    continue;
                }

                /* If this object is touching the top of the other object,
                * remember this so  we know we are on the floor. */
                has_touched_ground = has_touched_ground || (offset_before.y <= 0 && velocity_.y >= 0);

                /* Move the Y axis to free worldspace. This is done by moving
                 * this object so that there is min_distance_y distance between
                 * the objects on the Y axis. */
                position_.y = offset_before.y < 0
                    ? check->position_.y - min_distance_y
                    : check->position_.y + min_distance_y;

                /* If the object is not on the ground, reset the velocity in
                * this axis. */
                velocity_.y = 0;
			}


        }
    }

    /* Store whether we have touched the ground in onGround_. */
    onGround_ = has_touched_ground;
}

void GameObject::entered_collision(GameScene *scene, GameObject *collider, Vector2 collision) {
	
}