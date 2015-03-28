#include "EnnemyDog.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)


#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (36)
#define TEXTURE_HEIGHT      (28)


EnnemyDog::EnnemyDog(Vector2 pos) :Ennemis(pos, SpriteSheet::get("spr/metalgearsheet.bmp")){

	velocity_ = Vector2(WALK_SPEED, 0);
}

EnnemyDog :: ~EnnemyDog(){}

void EnnemyDog::render(Viewport &vp) {
	if (is_dead_state(state())){
		return;
	}
	Texture texture_left = {
		75, 280,
		33, 18
	};
	Texture texture_right = {
		236, 280,
		33, 18
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
	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;


	spriteSheet()->draw(tex, position_, vp);
		
}

void EnnemyDog::update(GameScene *scene, double delta, Keys keys){
	if (is_dead_state(state())){
		return;
	}
	animationTime_ += delta;


	/* Update the enemi animation. */
	AnimationState new_state = get_animation_state(animationFrames_);

	if (state_ != new_state) {
		state_ = new_state;
		animationIndex_ = 0;
	}
	else if (animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;
	
		animationIndex_ = (animationIndex_ + 1) % 2;
}

	process_gravity(delta);
}

EnnemyDog::AnimationState EnnemyDog::get_animation_state(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving right. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving left. */
		frames = 3;
		return RUN_LEFT;
	}

    return RUN_RIGHT;/* todo: make an idle state? */
}