/**
 * Ennemis.cpp
 * Defines the abstract Ennemis class.
 */

#include "Ennemis.h"
#include "GameScene.h"
#include "Actor.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)


Ennemis::Ennemis(Vector2 pos, SpriteSheet *spriteSheet) :Actor(pos, Vector2(16, 16)){
    spriteSheet_ = spriteSheet;
}
void Ennemis::go_left(double delta){

	Vector2 hAccel = { -(WALK_ACCEL + abs(velocity_.x)),0};
	velocity_ += hAccel*delta;
}

void Ennemis::go_right(double delta){

	Vector2 hAccel = { WALK_ACCEL + abs(velocity_.x), 0 };
	velocity_ += hAccel*delta;
}

void Ennemis::update(GameScene *scene, double delta, Keys keys){
	if (state() == DEAD){
		return;
	}

	process_gravity(delta);
}

void Ennemis::entered_collision(GameScene *scene, GameObject *obj, Vector2 vec) {
    if (state() == DEAD){
		return;
	}
	
	if (obj == scene->player()){
		
		if (scene->player()->velocity().y > 0 && scene->player()->position().y < position_.y){
			state(Actor::DEAD);
			isSolid_ = false;
            scene->player()->add_velocity(Vector2(0, -(scene->player()->velocity().y) * 2));
            scene->add_score(5);
		}
        else if (!scene->player()->is_sneaking()){
			scene->player()->state(Actor::DEAD);
		}
	}
	if (obj != scene->player() && obj->is_solid()){
        if (abs(vec.y) < abs(vec.x))
		{
            if (vec.x < 0){
                go_right(1);
			}
            if (vec.x > 0){
                go_left(1);
			} 
		}
	}
}