/**
 * EnnemyFlying.cpp
 * Defines the EnnemyFlying class.
 */

#include "EnnemyFlying.h"
#include <math.h>

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define M_PI		(3.14159265358979323846)



#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (18) 
#define TEXTURE_HEIGHT      (18) 

	EnnemyFlying::EnnemyFlying(Vector2 pos) :Ennemis(pos, SpriteSheet::get("spr/Zelda_Enemies_Sprite.bmp")){
		velocity_ = Vector2(-WALK_SPEED, -WALK_SPEED);
		start_position_ = pos;

}

EnnemyFlying :: ~EnnemyFlying(){}

void EnnemyFlying::render(Viewport &vp) {
    if (state() == DEAD){
		return;
	}

	Texture texture_left = { 
		56, 241,
		18, 18
	};
	Texture texture_right = {
		56, 241,
		18, 18
	};

	Texture tex = texture_right;

	switch (state_) {
	case RUN_RIGHT:
		tex = texture_right;
		break;
	case RUN_LEFT:
		tex = texture_left;
		break;
	}
	//The Enemie don't have animation

	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;


    sprite_sheet()->draw(tex, position_, vp);

}

void EnnemyFlying::update(GameScene *scene, double delta, Keys keys){
    if (state() == DEAD){
		return;
	}

	animationTime_ += delta;

	nbTick_++;

    if (position_.y < start_position_.y - 100){
		go_down(delta, nbTick_); //GoDown
	}

    if (position_.y > start_position_.y || is_on_ground()){
		go_up(delta, nbTick_); //GoUp
	}
    if (position_.x <= start_position_.x - 100){
		go_right(delta); 
	}

    if (position_.x >= start_position_.x + 100){
		go_left(delta);
	}
	/* Update the player animation. */
	AnimationState new_state = get_animation_state(animationFrames_);

	/*There no falling fonction because the enemie fly*/
}

EnnemyFlying::AnimationState EnnemyFlying::get_animation_state(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving Up. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving Down. */
		frames = 3;
		return RUN_LEFT;
    }

    return RUN_RIGHT;/* todo: make an idle state? */
}


void EnnemyFlying::go_down(double delta,int nbTick){ //Go Down

	Vector2 hAccel1 = { 0, (400 * abs(sin(nbTick * 0.5 * M_PI))) + abs(velocity_.y )};
	
	velocity_ += hAccel1*delta;
}

void EnnemyFlying::go_up(double delta,int nbTick){ //Go UP

	Vector2 hAccel1 = {0, -((400*abs(sin(nbTick * 0.5 * M_PI))) + abs(velocity_.y))};

	velocity_ += hAccel1*delta;
}